#include <poll.h>

namespace posix {

template<typename T>
class add_poll_events : public T {
public:
    using parent = T;
    template<int FDS_SIZE>
    void process_events(auto& fds) {
        if (fds[FD_INDEX].revents) {
            parent::process_event<FD_INDEX>(fds[FD_INDEX].revents); // dispatch event according to index.
        }
        process_events<FDS_SIZE-1>(fds);
    }
    template<>
    void process_events<0>(auto& fds) {
    }
    void poll_events() {
        auto fds = parent::get_fds(); // fds should be a array: meaning it has constexpr array size.
        int ret = poll(fds.data(), fds.size(), -1);
        if (ret == -1) {
            throw std::system_error(errno, std::error_category::system_category);
        }
        process_events<fds.size()>(fds);
    }
};

} // namespace posix
