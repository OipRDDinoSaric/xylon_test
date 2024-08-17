#include <fmt/core.h>
#include <Timer.hpp>
#include <Scheduler.hpp>


void callback()
{
    fmt::print("Hello from the callback!");
}

int
main()
{
    using std::literals::chrono_literals::operator""ms;

    constexpr static bool kDoesTimerRepeat {true};

    Xylon::Scheduler scheduler{};
    Xylon::Timer timer {scheduler};

    timer.start(10ms, callback, kDoesTimerRepeat);

    timer.cancel();

    return 0;
}
