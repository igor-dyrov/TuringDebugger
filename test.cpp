#include "TM.hpp"

int main()
{
    std::vector<Turing::Command> commands(9);
    commands[0].new_symbol = "1";
    commands[0].new_state = "q1";
    commands[0].move = Turing::Command::Right;
    commands[1].new_symbol = "0";
    commands[1].new_state = "q1";
    commands[1].move = Turing::Command::Right;
    commands[2].new_symbol = "lambda";
    commands[2].new_state = "q2";
    commands[2].move = Turing::Command::Left;
    commands[3].new_symbol = "0";
    commands[3].new_state = "q2";
    commands[3].move = Turing::Command::Left;
    commands[4].new_symbol = "1";
    commands[4].new_state = "q3";
    commands[4].move = Turing::Command::Left;
    commands[5].new_symbol = "1";
    commands[5].new_state = "Stop";
    commands[5].move = Turing::Command::Center;
    commands[6].new_symbol = "0";
    commands[6].new_state = "q3";
    commands[6].move = Turing::Command::Left;
    commands[7].new_symbol = "1";
    commands[7].new_state = "q3";
    commands[7].move = Turing::Command::Left;
    commands[8].new_symbol = "lambda";
    commands[8].new_state = "Stop";
    commands[8].move = Turing::Command::Right;
    transitions_set pairs;
    pairs.insert({Turing::Situation{"q1", "1"}, commands[0]});
    pairs.insert({Turing::Situation{"q1", "0"}, commands[1]});
    pairs.insert({Turing::Situation{"q1", "lambda"}, commands[2]});
    pairs.insert({Turing::Situation{"q2", "1"}, commands[3]});
    pairs.insert({Turing::Situation{"q2", "0"}, commands[4]});
    pairs.insert({Turing::Situation{"q2", "lambda"}, commands[5]});
    pairs.insert({Turing::Situation{"q3", "0"}, commands[6]});
    pairs.insert({Turing::Situation{"q3", "1"}, commands[7]});
    pairs.insert({Turing::Situation{"q3", "lambda"}, commands[8]});
    belt_type b = {{0,"1"}, {1, "1"}, {2, "1"}, {3, "1"}, {4, "1"}};
    Turing::Belt belt(b);
    Turing::Handler TM(pairs, belt, "q1", {"Stop"});
    Turing::ResultCode code = Turing::NormalWork;
    while (code == Turing::NormalWork) {
        code = TM.OneStep();
    }
    return 0;
}

