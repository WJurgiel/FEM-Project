//
// Created by Wojtek on 10.11.2024.
//

#include "Timer.h"

Timer::Timer() {
    std::cout << "[TIMER]: Timer object initialized.\n";
}

void Timer::start() {
    startPoint = std::chrono::high_resolution_clock::now();
}
void Timer::stop() {
    endPoint = std::chrono::high_resolution_clock::now();
}
double Timer::timeElapsed() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint).count() / 1000.0;
}
