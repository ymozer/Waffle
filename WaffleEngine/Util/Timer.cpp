#include "Timer.hpp"
#include <thread>

Timer::Timer() : m_isRunning(false) {}

void Timer::start() {
    m_startTime = std::chrono::high_resolution_clock::now();
    m_isRunning = true;
}

void Timer::stop() {
    m_endTime = std::chrono::high_resolution_clock::now();
    m_isRunning = false;
}

double Timer::elapsedMilliseconds() const {
    if (m_isRunning) {
        auto endTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(endTime - m_startTime).count();
    } else {
        return std::chrono::duration<double, std::milli>(m_endTime - m_startTime).count();
    }
}

double Timer::elapsedSeconds() const {
    return elapsedMilliseconds() / 1000.0;
}

void Timer::wait(double milliseconds) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(milliseconds)));
}
