//
// Created by Wojtek on 10.11.2024.
//

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
using TimePoint = std::chrono::high_resolution_clock::time_point;
class Timer {
private:
    TimePoint startPoint;
    TimePoint endPoint;
    double timeElapsed() const;
public:
    /*
     * initialize timer object
     * use .start() to startTimer
     * use .stop () stop timer
     * use << to output the elapsed time
    */
    Timer();
    void start();
    void stop();
    friend std::ostream& operator<<(std::ostream& os, const Timer& timer);
};
inline std::ostream& operator<<(std::ostream& os, const Timer& timer) {
    os << "[TIMER]: Time elapsed: " << timer.timeElapsed() << " s.";
    return os;
}


#endif //TIMER_H
