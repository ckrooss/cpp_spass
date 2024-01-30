#include "sm.h"

int main() {
    StateMachine sm;
    sm.change_state<Idle>();
    sm.process_event(CookingLimitReached{});
    sm.process_event(WarningAccepted{});
}