#pragma once
#include <iostream>
#include <variant>

template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

#define PRINT_FN std::cout << __PRETTY_FUNCTION__ << std::endl;
struct eCookingLimitReached {};
struct eWarningAccepted {};

struct WarningMessage {
    WarningMessage() {
        PRINT_FN
    }

    ~WarningMessage() {
        PRINT_FN
    }
};

struct StateMachine {
    struct Idle {
        Idle() {PRINT_FN}
        ~Idle() {PRINT_FN}
    };
    struct WarningShown {
        WarningShown() {PRINT_FN}
        ~WarningShown() {PRINT_FN}

        WarningMessage m_msg;
    };

    std::variant<Idle*, WarningShown*> m_state = new Idle();

    template<typename State>
    void transition() {
        std::visit([this](auto* state) {
            delete state;
        }, m_state);
        m_state = new State();
    }

    constexpr void process_event(const eCookingLimitReached& event) {
        std::visit(Overload{
            [&](Idle*) { PRINT_FN; transition<WarningShown>(); },
            [] (auto&) {PRINT_FN}
        }, m_state);
    }

    constexpr void process_event(const eWarningAccepted& event) {
        std::visit(Overload{
            [&](WarningShown*) { PRINT_FN; transition<Idle>(); },
            [] (auto&) {PRINT_FN}
        }, m_state);
    }

    void update(int cookingTime) {
        if(cookingTime > 300) {
            process_event(eCookingLimitReached{});
        }
    }
};


int main() {
    StateMachine sm;
    sm.update(100);
    sm.update(400);
    sm.process_event(eWarningAccepted{});
    sm.process_event(eWarningAccepted{});
}