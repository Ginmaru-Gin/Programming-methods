//
// Created by ginmaru on 9/14/22.
//

#pragma once

#include <chrono>

using
    std::chrono::system_clock,
    std::chrono::time_point;

class Timer {
    time_point<system_clock> start_point, end_point;

public:

    inline void start() {
        start_point = system_clock::now();
    }

    inline void stop() {
        end_point = system_clock::now();
    }

    [[nodiscard]] inline long nanosec() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_point - start_point).count();
    }

    [[nodiscard]] inline long microsec() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(end_point - start_point).count();
    }

    [[nodiscard]] inline long millisec() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_point - start_point).count();
    }

    [[nodiscard]] inline long sec() const {
        return std::chrono::duration_cast<std::chrono::seconds>(end_point - start_point).count();
    }

    [[nodiscard]] inline std::string to_string(const std::string& str = "") const {
        return str +
               std::to_string(sec()) + "s " +
               std::to_string(millisec() % 1000) + "ms " +
               std::to_string(microsec() % 1000) + "mcs " +
               std::to_string(nanosec() % 1000) + "ns";
    }

};
