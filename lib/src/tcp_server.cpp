#include "tcp_server.h"
#include "message.h"
#include "message_handler.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

namespace tcp {

TcpServer::TcpServer(const uint16_t port, IMessageHandler &message_handler)
    : port_{port}, message_handler_(message_handler) {}

TcpServer::~TcpServer() {
  if (const auto ret = Stop(); ret.has_value()) {
    std::cerr << *ret << std::endl;
  }

  if (listen_fd_ != -1) {
    close(listen_fd_);
  }
}

[[nodiscard]] OpResult TcpServer::Start() {
  listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd_ == -1) {
    return std::strerror(errno);
  }

  const int optval = 1;
  if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &optval,
                 sizeof(optval)) == -1) {
    return std::strerror(errno);
  }

  sockaddr_in server{};
  server.sin_family = AF_INET;
  server.sin_port = htons(port_);
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(listen_fd_, (sockaddr *)&server, sizeof(sockaddr_in)) == -1) {
    return std::strerror(errno);
  }

  if (listen(listen_fd_, 32) == -1) {
    return std::strerror(errno);
  }

  listen_thread_ = std::async([&]() {
    std::vector<pollfd> fd_list;
    fd_list.reserve(1000);
    fd_list.push_back({.fd = listen_fd_, .events = POLLIN});

    run_.store(true);
    bool has_client = false;
    auto timeout = -1;
    sockaddr_in client{};
    auto client_size = sizeof(sockaddr_in);
    while (run_) {
      const auto ret = poll(fd_list.data(), fd_list.size(), timeout);
      if (ret < 0) {
        std::cerr << "poll error: " << std::strerror(errno) << std::endl;
        break;
      }
      if (ret > 0) {
        for (const auto &pfd : fd_list) {
          if (pfd.revents & POLLIN) {
            if (pfd.fd == listen_fd_) {
              const auto new_client_fd = accept(listen_fd_, nullptr, nullptr);
              if (new_client_fd == -1) {
                std::cerr << "accept error: " << std::strerror(errno)
                          << std::endl;
                break;
              }

              fd_list.push_back({.fd = new_client_fd, .events = POLLIN});

              std::cout << "New Client Connected!\n";
              break;
            } else {
              Message new_mes{};
              new_mes.curr_buf_size =
                  recv(pfd.fd, new_mes.buf.data(), kMaxBufSize, 0);
              new_mes.sender_fd = pfd.fd;

              if (const auto ret = message_handler_.Execute(std::move(new_mes));
                  ret.has_value()) {
                std::cerr << *ret << std::endl;
              }
            }
          }
        }
      }
    }
  });

  return {};
}

[[nodiscard]] OpResult TcpServer::Stop() {
  if (run_.load()) {
    run_.store(false);

    if (listen_thread_.valid()) {
      listen_thread_.get();
    }
  }

  return {};
}

} // namespace tcp
