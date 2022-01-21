#ifndef TCP_MESSAGE_HANDLER_H_
#define TCP_MESSAGE_HANDLER_H_

#include "message_handler.h"

class TcpMessageHandler : public tcp::IMessageHandler {
public:
  [[nodiscard]] virtual tcp::OpResult
  Execute(tcp::Message &&received_mes) override {
    return {};
  }
};

#endif //! TCP_MESSAGE_HANDLER_H_