#pragma once

#include <chrono>

namespace Waffle
{
    class Timer
    {
    public:
        Timer();
        void start();
        void stop();
        double elapsedMilliseconds() const;
        double elapsedSeconds() const;
        void wait(double milliseconds) const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
        bool m_isRunning;
    };
} // namespace Waffle
