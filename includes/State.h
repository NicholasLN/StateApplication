// State.h
#pragma once

#include <memory>
#include <map>
#include <string>
#include <typeindex>
#include <chrono>
#include <sstream>
#include <iomanip>

class StateManager; // Forward declaration

class State {
protected:
    StateManager& manager;
    // Last modification timestamp
public:
    State(StateManager& m);
    virtual ~State() = default;
    StateManager& getManager();

    [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> getCreationTime() const { return createdAt; }
    [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> getLastModifiedTime() const { return lastModified; }

    template <typename Clock, typename Duration>
    std::string timePointToString(const std::chrono::time_point<Clock, Duration>& timePoint) {
        std::time_t time = Clock::to_time_t(timePoint);
        std::tm tm = *std::gmtime(&time);  // Use std::localtime if you want local time instead of UTC

        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    std::chrono::time_point<std::chrono::system_clock> createdAt;
    std::chrono::time_point<std::chrono::system_clock> lastModified;
};

template<typename T>
class PrimitiveTypeWrapper : public State {
public:
    T value;
    size_t indexInStateMap;  // Index in the StateManager's stateMap
    std::type_index typeInfo;  // Type information
    std::chrono::time_point<std::chrono::system_clock> createdAt;  // Creation timestamp
    std::chrono::time_point<std::chrono::system_clock> lastModified;  // Last modification timestamp

    PrimitiveTypeWrapper(StateManager& m, T initialValue, size_t index)
            : State(m), value(initialValue), indexInStateMap(index), typeInfo(typeid(T)),
              createdAt(std::chrono::system_clock::now()), lastModified(createdAt) {}

    // Function to update the value and modification timestamp
    void updateValue(const T& newValue) {
        value = newValue;
        lastModified = std::chrono::system_clock::now();
    }
};
