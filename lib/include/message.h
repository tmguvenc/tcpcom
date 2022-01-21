#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <array>
#include <cstdint>

namespace tcp {

static constexpr auto kMaxBufSize = 4 * 1024;

struct Message {
  int sender_fd{};
  std::array<char, kMaxBufSize> buf{};
  uint32_t curr_buf_size{0};
};

} // namespace tcp

#endif //! MESSAGE_H_