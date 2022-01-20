#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <atomic>
#include <cstdint>
#include <future>
#include <vector>

namespace tcp {

class TcpServer {
public:
  explicit TcpServer(const uint16_t port);
  ~TcpServer();

  void Start();
  void Stop();

  TcpServer(const TcpServer &) = delete;
  TcpServer &operator=(const TcpServer &) = delete;
  TcpServer(TcpServer &&) = delete;
  TcpServer &operator=(TcpServer &&) = delete;

private:
  int listen_fd_{};
  std::vector<int> fds_{};

  std::future<void> listen_thread_;
};

} // namespace tcp

#endif //! TCP_SERVER_H_