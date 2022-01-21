#include "tcp_message_handler.h"
#include "tcp_server.h"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  TcpMessageHandler mes_handler{};
  tcp::TcpServer server(5555, mes_handler);

  if (const auto res = server.Start(); res.has_value()) {
    std::cerr << *res << std::endl;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  if (const auto res = server.Start(); res.has_value()) {
    std::cerr << *res << std::endl;
  }

  return 0;
}