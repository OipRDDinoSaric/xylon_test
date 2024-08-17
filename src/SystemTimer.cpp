/**
 * @file
 *
 */

#include <SystemTimer.hpp>

#include <chrono>

/**
 * @brief Defined by another library.
 *
 * @param[in] timeout
 * @param[in] callback
 */
void
sysStartTimer([[maybe_unused]] std::uint64_t timeout,
              void (*)(void* pScheduler),
              [[maybe_unused]] void* pScheduler)
{}

/**
 * @brief Defined by another library.
 *
 * @return Current number of ticks in microseconds.
 */
std::chrono::microseconds
sysTimerTick()
{
    using std::chrono_literals::operator""ms;
    return 0ms;
};

namespace Xylon
{
void
SystemTimer::start(const std::chrono::microseconds timeout, CallbackType callback, void* pScheduler)
{
    sysStartTimer(static_cast<uint64_t>(timeout.count()), callback, pScheduler);
}

std::chrono::microseconds
SystemTimer::currentTick()
{
    return sysTimerTick();
}

}  // namespace Xylon