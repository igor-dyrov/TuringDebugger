#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using symbol = std::string;
using state = std::string;
using belt_type = std::map<int, std::string>;

template <class T>
bool Owns(const std::vector<T> &, const T &);

namespace Turing {
    enum ResultCode {EndOfProgram, NormalWork, NoSuitableCommand};
    struct Command {
        enum direction { Right, Left, Center } move;
        symbol new_symbol;
        state new_state;
    };
}

using transitions_set = std::map<std::pair<state, symbol>, Turing::Command>;

namespace Turing {
    class Belt {
    private:
        const symbol lambda = "lambda";
        belt_type internal_belt;
    public:
        Belt(){};
        Belt(const belt_type&);
        Belt& operator = (const Belt &);
        symbol& operator[](int);
        friend std::ostream & operator << (std::ostream &, const Belt &);
    };

    class Handler {
    public:
        int temp_index;
        state temp_state;
        state beg_state;
        std::vector<state> end_states;
        transitions_set transitions;
        Belt belt;
        Turing::Command get_transition(const std::pair<state, symbol> &);
    //public:
        Handler(const transitions_set &, const Belt &, const state &, const std::vector<state> &);
        ResultCode OneStep();
    };
}
