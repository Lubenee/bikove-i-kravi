#if !defined(TIMER_H)
#define TIMER_H

#include <chrono>

class Timer {
public:
    void start() {
        start_time = std::chrono::steady_clock::now();
    }

    int elapsed_seconds() const {
        auto end_time = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    }

private:
    std::chrono::steady_clock::time_point start_time;
};

#endif // TIMER_H
