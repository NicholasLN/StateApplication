//
// Created by nicho on 1/19/2024.
//

#include "State.h"

State::State(StateManager& m) : manager(m) {}
StateManager& State::getManager() { return manager; }
