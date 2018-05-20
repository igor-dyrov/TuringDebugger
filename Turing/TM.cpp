#include "TM.hpp"
#include "Lang.hpp"


int get_min_key(belt_type &belt) {
    if (belt.empty())
        return 0;
    else
        return belt.begin()->first;
}

namespace Turing {
    bool operator<(const Situation &s1, const Situation &s2) {
        return  (s1._state < s2._state ||
                (s1._state == s2._state && s1._symbol < s2._symbol));
    }
    bool operator==(const Situation &s1, const Situation &s2) {
        return s1._state == s2._state && s1._symbol == s2._symbol;
    }

    bool operator!=(const Situation &s1, const Situation &s2) {
        return s1._state != s2._state || s1._symbol != s2._symbol;
    }
}

Turing::Belt::Belt() {
    beg_index = 0;
}

Turing::Belt::Belt(const belt_type &belt) {
    internal_belt = belt;
    beg_index = get_min_key(internal_belt);
}

Turing::Belt& Turing::Belt::operator=(const Turing::Belt & obj) {
    internal_belt = obj.internal_belt;
    beg_index = obj.beg_index;
    return *this;
}

int Turing::Belt::Begin() { return beg_index; }

void Turing::Belt::clear() {
    internal_belt.clear();
    beg_index = 0;
}

symbol& Turing::Belt::operator[](int index) {
    if (std::find_if(internal_belt.begin(), internal_belt.end(),[&index](auto &i){
        if (i.first == index) return true; return false;})== internal_belt.end()) {
        internal_belt.insert({index, lambda});
    }
    beg_index = get_min_key(internal_belt);
    return internal_belt[index];
}

const belt_type &Turing::Belt::getBelt() const
{
    return internal_belt;
}

namespace Turing {
    std::ostream &operator << (std::ostream &os, const Turing::Belt &obj) {
        for (auto const &i : obj.internal_belt)
            os << "{{" << i.first << "}{" << i.second << "}} ";
        os << '\n';
        return os;
    }
}

//Turing::Handler::Handler(const transitions_set &dict, const Belt &new_belt,
//                         const state &beg, const std::vector<state> &end) {
//    transitions = dict;
//    belt = new_belt;
//    beg_state = beg;
//    temp_state = beg_state;
//    end_states = end;
//    temp_index = belt.Begin();
//}

void Turing::Handler::setBelt(const Belt &new_belt)
{
    belt = new_belt;
    temp_index = belt.Begin();
}

void Turing::Handler::setFields(const transitions_set &dict, const Belt &new_belt,
               const state &beg, const std::vector<state> &end)
{
    transitions = dict;
    beg_state = beg;
    temp_state = beg_state;
    end_states = end;
}

std::string Turing::Handler::GetBeltValues() {
    std::stringstream str;
    str << belt;
    return str.str();
}

Turing::Handler &Turing::Handler::instance()
{
    static Turing::Handler object;
    return object;
}

Turing::ResultCode Turing::Handler::OneStep() {
    if (std::find(end_states.begin(), end_states.end(),temp_state) == end_states.end()) {
        Situation temp;
        temp._state = temp_state;
        temp._symbol = belt[temp_index];
        Command to_do = transitions[temp];
        if (to_do.new_state == "" || to_do.new_symbol == "")
        {
            return NoSuitableCommand;
        }
        else
        {
            change current;
            current.temp_index = temp_index;
            current.temp_state = temp_state;
            current.s = belt[temp_index];
            history.push(current);
        }
        belt[temp_index] = to_do.new_symbol;
        if (to_do.move == Command::Right)
            ++temp_index;
        else if(to_do.move == Command::Left)
            --temp_index;
        temp_state = to_do.new_state;
        if (std::find(end_states.begin(), end_states.end(),temp_state) == end_states.end())
            return ResultCode::NormalWork;
        else
            return ResultCode::EndOfProgram;
    }
    else return ResultCode::EndOfProgram;
}

Turing::ResultCode Turing::Handler::StepBefore()
{
    if ( history.empty() )
    {
        return ResultCode::EndOfProgram;
    }
    else
    {
        change last = history.top();
        temp_index = last.temp_index;
        temp_state = last.temp_state;
        belt[temp_index] = last.s;
        history.pop();
        return ResultCode::NormalWork;
    }
}

void Turing::Handler::clear() {
    beg_state = "";
    end_states.clear();
    temp_state = "";
    temp_index = belt.Begin();
    transitions.clear();
}

void Turing::Handler::SetCommands(request_pool &pool) {
    while (!pool.empty()) {
        auto request = pool.front();
        if (request.type_of_action == TuringRequest::set_beg) {
            beg_state = request.params[0];
            temp_state = beg_state;
            pool.pop();
        }
        else if (request.type_of_action == TuringRequest::set_end) {
            end_states.clear();
            for (auto &i : request.params)
                end_states.push_back(i);
            pool.pop();
        }
        else if(request.type_of_action == TuringRequest::transition) {
        	if (request.params.size() < 5)
            {
                std::string er ="";
                for (auto& obj : request.params ){
                    er += obj;
                    er += " ";
                }
                throw InterpretException("bad options: " + er);
            }
            Turing::Command cmd;
            if (request.params[4] == "L")
                cmd.move = Turing::Command::Left;
            else if (request.params[4] == "R")
                cmd.move = Turing::Command::Right;
            else
                cmd.move = Turing::Command::Center;
            cmd.new_symbol = request.params[2];
            cmd.new_state = request.params[3];
            transitions.insert({Turing::Situation{request.params[1], request.params[0]}, cmd});
            pool.pop();
        }
    }
}

bool Turing::Handler::isFirst()
{
    return history.empty();
}

const Turing::Belt& Turing::Handler::getBelt() const
{
    return belt;
}

const int Turing::Handler::get_temp_index() const
{
    return temp_index;
}

