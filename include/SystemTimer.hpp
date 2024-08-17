/**
 * @file
 *
 */

#pragma once

#include <chrono>

namespace Xylon
{

class SystemTimer
{
public:
    using CallbackType = void (*)(void* pScheduler);

    SystemTimer() = delete;

    static void
    start(std::chrono::microseconds timeout, CallbackType callback, void* pScheduler);

    static std::chrono::microseconds
    currentTick();

private:
};
}  // namespace Xylon