#include "tcp_server.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace tcp {

TcpServer::TcpServer(const uint16_t port) {
  listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);

  const int optval = 1;
  setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  sockaddr_in server{};
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;

  bind(listen_fd_, (sockaddr *)&server, sizeof(sockaddr_in));
}

TcpServer::~TcpServer() {
  if (listen_fd_ != -1) {
    close(listen_fd_);
  }
}

void TcpServer::Start() {
  listen_thread_ = std::async([&]() {

  });
}

void TcpServer::Stop() {}

} // namespace tcp
