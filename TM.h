#include <iostream>
#include <vector>
#include <unordered_map>

namespace Turing {

    using symbol = std::string;
    using state = std::string;
    using belt_type = std::vector<std::string>;

    struct pairhash {
    public:
        template <typename T, typename U>
        std::size_t operator()(const std::pair<T, U> &x) const
        {
            return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
        }
    };

    class Command {
    public:
        Command();
        Command(const std::string&);
        ~Command();
    //private:
        enum direction { Right, Left } move;
        symbol new_symbol;
        state new_state;
    };

    using transitions_set = std::unordered_map<std::pair<state, symbol>, Command, pairhash>;

    class Handler {
    private:
        state beg_state;
        belt_type belt;
        transitions_set transitions;
    public:
        Handler(const transitions_set &, const belt_type&);
        ~Handler();
        void OneStep();
    };
}



#include "TM.hpp"