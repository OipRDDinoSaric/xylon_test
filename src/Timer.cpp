/**
 * @file
 *
 */

#include <Timer.hpp>

#include <Scheduler.hpp>

namespace Xylon
{
Timer::Timer(Scheduler& scheduler) :
        scheduler {scheduler},
        timeoutSinceEpoch {},
        isRepeatable {false},
        callback {}
{}

void
Timer::start(const std::chrono::microseconds newTimeout,
             CallbackType                    newCallback,
             const bool                      newDoRepeat)
{
    timeout      = newTimeout;
    callback     = newCallback;
    isRepeatable = newDoRepeat;
    scheduler.schedule(*this);
}

void
Timer::cancel()
{
    scheduler.cancel(*this);
}

void
Timer::setTimeoutSinceEpoch(std::chrono::microseconds newTimeoutSinceEpoch) noexcept
{
    timeoutSinceEpoch = newTimeoutSinceEpoch;
}

void
Timer::setNextTimeoutSinceEpoch() noexcept
{
    timeoutSinceEpoch += timeout;
}

std::chrono::microseconds
Timer::getTimeout() const noexcept
{
    return timeout;
}

std::chrono::microseconds
Timer::getTimeoutSinceEpoch() const noexcept
{
    return timeoutSinceEpoch;
}

bool
Timer::getIsRepeatable() const noexcept
{
    return isRepeatable;
}

auto
Timer::getCallback() const noexcept -> CallbackType
{
    return callback;
}
}  // namespace Xylon