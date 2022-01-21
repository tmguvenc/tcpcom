#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "common.h"
#include <atomic>
#include <cstdint>
#include <future>
#include <optional>

namespace tcp {

class IMessageHandler;

class TcpServer {
public:
  explicit TcpServer(const uint16_t port, IMessageHandler &message_handler);
  ~TcpServer();

  [[nodiscard]] OpResult Start();
  [[nodiscard]] OpResult Stop();

  TcpServer(const TcpServer &) = delete;
  TcpServer &operator=(const TcpServer &) = delete;
  TcpServer(TcpServer &&) = delete;
  TcpServer &operator=(TcpServer &&) = delete;

private:
  uint16_t port_{0};
  IMessageHandler &message_handler_;
  int listen_fd_{};
  std::future<void> listen_thread_;
  std::atomic_bool run_{false};
};

} // namespace tcp

#endif //! TCP_SERVER_H_