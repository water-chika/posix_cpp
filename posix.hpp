#include <poll.h>

#include <system_error>

namespace posix {

template<typename T>
class add_poll_events : public T {
public:
    using parent = T;
    void poll_events() {
        auto fds = parent::get_fds(); // fds should be a array: meaning it has constexpr array size.
        int ret = poll(fds.data(), fds.size(), 100);
        if (ret == -1) {
            throw std::system_error(errno, std::system_category());
        }
        parent::process_events(fds);
    }
};

template<typename T>
class add_empty_pollfd_array : public T {
public:
    using parent = T;
    static constexpr int FDS_SIZE = 0;
    void process_events(auto& fds) {
    }
    std::vector<pollfd> get_fds() {
        return {};
    }
};

} // namespace posix
