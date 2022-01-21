#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include "common.h"

namespace tcp {

class TcpClient {
public:
  explicit TcpClient(const std::string &ip, const uint16_t port);
  ~TcpClient();

  [[nodiscard]] OpResult Connect();

  TcpClient(const TcpClient &) = delete;
  TcpClient &operator=(const TcpClient &) = delete;
  TcpClient(TcpClient &&) = delete;
  TcpClient &operator=(TcpClient &&) = delete;

private:
  const std::string &ip_;
  uint16_t port_{0};
  int fd_{-1};
};

} // namespace tcp

#endif //! TCP_CLIENT_H_