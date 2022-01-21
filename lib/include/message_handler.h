#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_

#include "common.h"
#include "message.h"

namespace tcp {

class IMessageHandler {
public:
  virtual ~IMessageHandler() = default;
  [[nodiscard]] virtual OpResult Execute(Message &&received_mes) = 0;
};

} // namespace tcp

#endif //! MESSAGE_HANDLER_H_