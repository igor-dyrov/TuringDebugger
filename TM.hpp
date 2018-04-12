#include "settings.hpp"

int get_min_key(belt_type &);

namespace Turing {
    enum ResultCode {EndOfProgram, NormalWork, NoSuitableCommand};
    struct Situation {
        state _state;
        symbol _symbol;
        friend bool operator < (const Situation &, const Situation &);
        friend bool operator > (const Situation &, const Situation &);
        friend bool operator <= (const Situation &, const Situation &);
        friend bool operator >= (const Situation &, const Situation &);
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
        symbol& operator[](int);
        friend std::ostream & operator << (std::ostream &, const Belt &);
    };

    class Handler {
    private:
        int temp_index;
        state temp_state;
        state beg_state;
        std::vector<state> end_states;
        transitions_set transitions;
        Belt belt;
    public:
        Handler(const transitions_set &, const Belt &, const state &, const std::vector<state> &);
        ResultCode OneStep();
        void clear();
        void SetCommands(request_pool &);
    };
}
