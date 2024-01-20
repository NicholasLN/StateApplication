// StateManager.h
#pragma once

#include "State.h"
#include <shared_mutex>
#include <type_traits>
#include <mutex>
#include <vector>

class StateManager {
public:
    std::map<std::type_index, std::vector<std::shared_ptr<State>>> stateMap;
    std::map<std::string, std::shared_ptr<State>> taggedStates;
    mutable std::shared_mutex m;

    template<typename T, typename... Args>
    auto append(const std::string& tag, Args &&... args) {
        std::unique_lock<std::shared_mutex> lock(m);
        if constexpr (std::is_base_of<State, T>::value) {
            size_t index = stateMap[std::type_index(typeid(T))].size();
            auto newState = std::make_shared<T>(*this, std::forward<Args>(args)...);
            newState->createdAt = std::chrono::system_clock::now();  // Set creation timestamp
            newState->lastModified = newState->createdAt;  // Set modification timestamp
            stateMap[std::type_index(typeid(T))].push_back(newState);
            taggedStates[tag] = newState;
            return newState;
        } else {
            size_t index = stateMap[std::type_index(typeid(PrimitiveTypeWrapper<T>))].size();
            auto wrapper = std::make_shared<PrimitiveTypeWrapper<T>>(*this, std::forward<Args>(args)..., index);
            stateMap[std::type_index(typeid(PrimitiveTypeWrapper<T>))].push_back(wrapper);
            taggedStates[tag] = wrapper;
            return wrapper;
        }
    }

    std::shared_ptr<State> getByTag(const std::string& tag);
};

class StateManagerLocator {
private:
    static StateManager stateManager;
public:
    static StateManager& getStateManager();
};
