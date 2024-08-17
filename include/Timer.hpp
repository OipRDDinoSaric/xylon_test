/**
 * @file
 *
 */

#pragma once

#include <chrono>

namespace Xylon
{
class Scheduler;
}

namespace Xylon
{
class Timer
{
public:
    using CallbackType = void (*)();

    explicit Timer(Scheduler& scheduler);

    void
    start(std::chrono::microseconds newTimeout, CallbackType newCallback, bool newDoRepeat);

    void
    cancel();

    void
    setTimeoutSinceEpoch(std::chrono::microseconds newTimeout) noexcept;

    [[nodiscard]] std::chrono::microseconds
    getTimeoutSinceEpoch() const noexcept;

    void
    setNextTimeoutSinceEpoch() noexcept;

    [[nodiscard]] std::chrono::microseconds
    getTimeout() const noexcept;

    [[nodiscard]] bool
    getIsRepeatable() const noexcept;

    [[nodiscard]] CallbackType
    getCallback() const noexcept;

    bool
    operator<(const Timer& other) const
    {
        return (timeoutSinceEpoch < other.timeoutSinceEpoch);
    }

    bool
    operator>(const Timer& other) const
    {
        return !(timeoutSinceEpoch < other.timeoutSinceEpoch);
    }

private:
    Scheduler& scheduler;

    std::chrono::microseconds timeoutSinceEpoch;
    std::chrono::microseconds timeout;
    bool                      isRepeatable;
    CallbackType              callback;
};
}  // namespace Xylon