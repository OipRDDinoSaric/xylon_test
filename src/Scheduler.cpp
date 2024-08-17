/**
 * @file
 *
 */

#include <Scheduler.hpp>
#include <SystemTimer.hpp>

#include <algorithm>

namespace Xylon
{
Scheduler::Scheduler() : timers {}
{}

void
Scheduler::schedule(Xylon::Timer& timer)
{
    std::lock_guard guard(mtxTimers);
    timer.setTimeoutSinceEpoch(timer.getTimeout() + SystemTimer::currentTick());

    timers.insert(calculatePositionIter(timer), timer);

    if (&timer == &(timers.begin()->get()))
    {
        scheduleFirstTimer();
    }
}

void
Scheduler::cancel(Timer& timer)
{
    std::lock_guard guard(mtxTimers);
    if (const auto timerPositionIter {getPositionIter(timer)}; timerPositionIter != timers.end())
    {
        bool isTimerFirst {timerPositionIter == timers.begin()};
        timers.erase(timerPositionIter);
        if (isTimerFirst)
        {
            if (timers.empty())
            {
                using std::chrono_literals::operator""ms;
                // This is dependent on the implementation of the underlying system timer. It
                // assumes it will not call a null pointer.
                SystemTimer::start(0ms, nullptr, this);
            }
            else
            {
                scheduleFirstTimer();
            }
        }
    }
}

[[nodiscard]] std::list<std::reference_wrapper<Xylon::Timer>>::iterator
Scheduler::calculatePositionIter(Xylon::Timer& timer)
{
    const auto comparer {[](const auto& first, const auto& second) -> bool
                         {
                             return (first.get() < second.get());
                         }};

    return std::ranges::lower_bound(timers, std::ref(timer), comparer);
}

void
Scheduler::callbackForwarderStatic(void* pScheduler)
{
    if (pScheduler != nullptr)
    {
        reinterpret_cast<Scheduler*>(pScheduler)->callbackForwarder();
    }
}

void
Scheduler::callbackForwarder()
{
    auto& elapsedTimer {timers.begin()->get()};

    rescheduleNextTimer();

    elapsedTimer.getCallback()();
}
void

Scheduler::scheduleFirstTimer()
{
    if (!timers.empty())
    {
        SystemTimer::start(timers.begin()->get().getTimeoutSinceEpoch(),
                           callbackForwarderStatic,
                           this);
    }
}

void
Scheduler::rescheduleNextTimer()
{
    std::lock_guard guard(mtxTimers);
    auto& elapsedTimer {timers.begin()->get()};

    timers.erase(timers.begin());

    if (elapsedTimer.getIsRepeatable())
    {
        elapsedTimer.setNextTimeoutSinceEpoch();
        timers.insert(calculatePositionIter(elapsedTimer), elapsedTimer);
    }

    scheduleFirstTimer();
}

[[nodiscard]] std::list<std::reference_wrapper<Xylon::Timer>>::const_iterator
Scheduler::getPositionIter(Xylon::Timer& timer)
{
    auto timerPositionIter {calculatePositionIter(timer)};
    do
    {
        if (&(timerPositionIter->get()) == &timer)
        {
            return timerPositionIter;
        }
        timerPositionIter++;
    }
    while (timerPositionIter != timers.end() &&
           timerPositionIter->get().getTimeoutSinceEpoch() == timer.getTimeoutSinceEpoch());

    return timers.end();
}
}  // namespace Xylon