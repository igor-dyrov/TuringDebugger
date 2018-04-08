#include "TM.hpp"

template <class T>
bool Owns(const std::vector<T> &set, const T &elem) {
    for (auto const &i : set) {
        if (i == elem)
            return true;
    }
    return false;
}

namespace Turing {
    bool operator<(const Situation &s1, const Situation &s2) {
        return s1._state < s2._state;
    }

    bool operator<=(const Situation &s1, const Situation &s2) {
        return s1._state <= s2._state;
    }

    bool operator>(const Situation &s1, const Situation &s2) {
        return s1._state > s2._state;
    }

    bool operator>=(const Situation &s1, const Situation &s2) {
        return s1._state >= s2._state;
    }

    bool operator==(const Situation &s1, const Situation &s2) {
        return s1._state == s2._state && s1._symbol == s2._symbol;
    }

    bool operator!=(const Situation &s1, const Situation &s2) {
        return s1._state != s2._state || s1._symbol != s2._symbol;
    }
}
Turing::Belt::Belt(const belt_type &belt) {
    internal_belt = belt;
}

Turing::Belt& Turing::Belt::operator=(const Turing::Belt & obj) {
    internal_belt = obj.internal_belt;
    return *this;
}

symbol& Turing::Belt::operator[](int index) {
    bool has_key = false;
    for (auto const &i : internal_belt) {
        if (i.first == index)
            has_key = true;
    }
    if (!has_key) {
        internal_belt.insert({index, lambda});
    }
    return internal_belt[index];
}

namespace Turing {
    std::ostream &operator << (std::ostream &os, const Turing::Belt &obj) {
        for (auto const &i : obj.internal_belt)
            os << "{{" << i.first << "}{" << i.second << "}} ";
        os << '\n';
        return os;
    }
}

Turing::Handler::Handler(const transitions_set &dict, const Belt &new_belt,
                         const state &beg, const std::vector<state> &end) {
    transitions = dict;
    belt = new_belt;
    beg_state = beg;
    temp_state = beg_state;
    end_states = end;
    temp_index = 0;
}

Turing::ResultCode Turing::Handler::OneStep() {
    if (!Owns(end_states, temp_state)) {
        Situation temp;
        temp._state = temp_state;
        temp._symbol = belt[temp_index];
        Command to_do = transitions[temp];
        if (to_do.new_state == "" || to_do.new_symbol == "")
            return NoSuitableCommand;
        belt[temp_index] = to_do.new_symbol;
        if (to_do.move == Command::Right)
            ++temp_index;
        else if(to_do.move == Command::Left)
            --temp_index;
        temp_state = to_do.new_state;
        std::cout << belt;
        if (!Owns(end_states, temp_state))
            return ResultCode::NormalWork;
        else
            return ResultCode::EndOfProgram;
    }
    else return ResultCode::EndOfProgram;
}

