#pragma once 
#include <iostream>

#define PRINT_FN std::cout << __PRETTY_FUNCTION__ << std::endl;
struct CookingLimitReached {};
struct DelayAccepted {};
struct LockAccepted {};
struct WarningAccepted {};
struct CleaningFinished {};

struct StateMachine;
struct State {
    State(StateMachine& sm) : m_sm(sm) {}
    virtual ~State() noexcept = default;
    virtual void exit() {};
    virtual void entry() {};
    virtual void process(const CookingLimitReached&) {};
    virtual void process(const DelayAccepted&) {};
    virtual void process(const LockAccepted&) {};
    virtual void process(const CleaningFinished&) {};
    virtual void process(const WarningAccepted&) {};
    virtual void update();

    StateMachine& m_sm;
};

struct StateMachine {
    template<typename S>
    void change_state() {
        if(m_state) {
            m_state->exit();
        }
        m_state = new S(*this);
        m_state->entry();
    }

    template<typename E>
    void process_event(const E& event) {
        m_state->process(event);
    }

    State* m_state{nullptr};
};



struct Idle;
struct WarningShown;

struct Idle : public State {
    using State::State;

    void entry() override {
        PRINT_FN
    }
    
    void exit() override {
        PRINT_FN
    }

    void process(const CookingLimitReached&) override {
        PRINT_FN
        m_sm.change_state<WarningShown>();
    }
};

struct WarningShown : public State {
    using State::State;

    void entry() override {
        PRINT_FN
    }

    void exit() override {
        PRINT_FN
    }

    void process(const WarningAccepted&) override {
        PRINT_FN
        m_sm.change_state<Idle>();
    }
};