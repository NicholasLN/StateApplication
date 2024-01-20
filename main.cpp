#include <iostream>


#include "includes/State.h"
#include "includes/StateManager.h"

class Time : public State {
    int tick;
public:
    Time(StateManager& m, int initial = 0) : State(m), tick(initial) {} // Modified constructor
    int getTick() {
        // Retrieve the state of x and increment its value by 4
        auto xState = std::dynamic_pointer_cast<PrimitiveTypeWrapper<int>>(manager.getByTag("x"));
        return tick;
    }
    void setTick(int newTick) { tick = newTick; }
};

int main() {
    auto& state = StateManagerLocator::getStateManager();

    auto time = state.append<Time>("time", 10); // Tagged as "time"
    auto x = state.append<int>("x", 92);
    auto y = state.append<int>("y", 2);

    //auto timeState = std::dynamic_pointer_cast<Time>(state.getByTag("time")); // Retrieve by tag
    //auto xState = std::dynamic_pointer_cast<PrimitiveTypeWrapper<int>>(state.getByTag("x"));
    //auto yState = std::dynamic_pointer_cast<PrimitiveTypeWrapper<int>>(state.getByTag("y"));

    if (time) {
        std::cout << "Time Tick: " << time->getTick() << std::endl;
    }

    if (x && y) {
        std::cout << "92+2: " << x->value + y->value << std::endl;
    }

    return 0;
}