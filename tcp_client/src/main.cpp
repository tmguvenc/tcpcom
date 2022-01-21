#include "tcp_client.h"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  tcp::TcpClient client("127.0.0.1", 5555);

  if (const auto res = client.Connect(); res.has_value()) {
    std::cerr << *res << std::endl;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(100000));

  return 0;
}