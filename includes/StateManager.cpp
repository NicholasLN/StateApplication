#include "StateManager.h"
StateManager StateManagerLocator::stateManager;

StateManager& StateManagerLocator::getStateManager() {
    return stateManager;
}
// Method to get a state by tag
std::shared_ptr<State> StateManager::getByTag(const std::string& tag) {
    auto it = taggedStates.find(tag);
    if (it != taggedStates.end()) {
        return it->second;
    }
    return nullptr; // Return null if not found
}