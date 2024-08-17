/**
 * @file
 *
 */

#pragma once

#include <chrono>
#include <functional>
#include <list>
#include <mutex>

#include <Timer.hpp>

namespace Xylon
{
class Scheduler
{
public:
    Scheduler();

    void
    schedule(Xylon::Timer& timer);

    void
    cancel(Xylon::Timer& timer);

private:
    constexpr static std::size_t kMaxNumberOfTimers {10};

    [[nodiscard]] std::list<std::reference_wrapper<Xylon::Timer>>::iterator
    calculatePositionIter(Xylon::Timer& timer);

    static void
    callbackForwarderStatic(void* pScheduler);

    void
    callbackForwarder();

    void
    scheduleFirstTimer();

    void
    rescheduleNextTimer();

    [[nodiscard]] std::list<std::reference_wrapper<Xylon::Timer>>::const_iterator
    getPositionIter(Xylon::Timer& timer);

    /**
     * This list is always sorted with the lowest time being first.
     *
     * Multiset might be more appropriate because it uses a red-black tree. This implementation
     * favors simplicity of converting to an implementation without dynamic memory.
     */
    std::list<std::reference_wrapper<Xylon::Timer>> timers;
    std::mutex mtxTimers;
};
}  // namespace Xylon