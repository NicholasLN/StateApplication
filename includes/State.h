// State.h
#pragma once

#include <memory>
#include <map>
#include <string>
#include <typeindex>
#include <chrono>

class StateManager; // Forward declaration

class State {
protected:
    StateManager& manager;
public:
    State(StateManager& m);
    virtual ~State() = default;
    StateManager& getManager();
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
