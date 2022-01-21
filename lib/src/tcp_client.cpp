#include "tcp_client.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

namespace tcp {

TcpClient::TcpClient(const std::string &ip, const uint16_t port)
    : ip_(ip), port_{port} {}

TcpClient::~TcpClient() {
  // if (const auto ret = Stop(); ret.has_value()) {
  //   std::cerr << *ret << std::endl;
  // }

  if (fd_ != -1) {
    close(fd_);
  }
}

[[nodiscard]] OpResult TcpClient::Connect() {
  fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (fd_ == -1) {
    return std::strerror(errno);
  }

  sockaddr_in server{};
  server.sin_family = AF_INET;
  server.sin_port = htons(port_);
  server.sin_addr.s_addr = inet_addr(ip_.c_str());

  if (connect(fd_, (sockaddr *)&server, sizeof(sockaddr_in)) == -1) {
    return std::strerror(errno);
  }

  return {};
}

} // namespace tcp
