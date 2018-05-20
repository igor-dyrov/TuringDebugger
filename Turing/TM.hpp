#ifndef __TM__
#define __TM__

#include "settings.hpp"

int get_min_key(belt_type &);

namespace Turing {
    enum ResultCode {EndOfProgram, NormalWork, NoSuitableCommand};
    struct Situation {
        state _state;
        symbol _symbol;
        friend bool operator < (const Situation &, const Situation &);
        friend bool operator == (const Situation &, const Situation &);
        friend bool operator != (const Situation &, const Situation &);
    };
    struct Command {
        enum direction { Right, Left, Center } move;
        symbol new_symbol;
        state new_state;
    };
}

namespace Turing {
    class Belt {
    private:
        const symbol lambda = "lambda";
        belt_type internal_belt;
        int beg_index;
    public:
        Belt();
        Belt(const belt_type&);
        void clear();
        int Begin();
        Belt& operator = (const Belt &);
        size_t size();
        symbol& operator[](int);
        const belt_type& getBelt() const;
        friend std::ostream & operator << (std::ostream &, const Belt &);
    };


    class Handler {
    private:
        Handler() = default;
        Handler(const Handler& );
        Handler& operator =(const Handler );
        int temp_index;
        state temp_state;
        state beg_state;
        std::vector<state> end_states;
        transitions_set transitions;
        Belt belt;
        struct change // хранит индекс, символ и состояние до перехода
        {
            change& operator =(const change& ) = default;
            int temp_index;
            state temp_state;
            symbol s;
        };
        std::stack<change> history;
    public:
        static Handler& instance();
        void setFields(const transitions_set &, const Belt &, const state &, const std::vector<state> &);
        void setBelt(const Belt &new_belt);
        ResultCode OneStep();
        ResultCode StepBefore();
        std::string GetBeltValues();
        void clear();
        void SetCommands(request_pool &);
        bool isFirst();
        const Belt& getBelt() const;
        const int get_temp_index() const;
    };
}

#endif
