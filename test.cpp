#include "TM.hpp"
#include "Lang.hpp"

int main()
{
    /*std::vector<Turing::Command> commands(9);
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
    }*/
    /*std::string s = "in { qqq, aaa, q1q1, R } do {qqq, aaa, q1q1, R}";
    boost::regex expr{"(?<cmd1>(\\w+))(\\s)*"
                "{(?<opt1>((\\s)*(\\w)+,*(\\s)*)*)}"
                "\\s*(?<cmd2>(\\w+))(\\s)*"
                "{(?<opt2>((\\s)*(\\w)+,*(\\s)*)*)}"};
    boost::smatch what;
    if (boost::regex_search(s, what, expr))
    {
        //std::cout << what["options"] << '\n';
    }
    std::string ss = what["cmd1"] + what["cmd2"];
    boost::regex param_expr{"\\w+"};
    boost::sregex_iterator xIt(ss.begin(), ss.end(), param_expr);
    while (xIt != boost::sregex_iterator{}){
        std::cout << *xIt++;
    }*/
    /*std::string example = {"set_end { q1 }; set_end {qstop, qend};"};
    TuringInterpreter intr;
    auto _pool = intr.Interpret(example);
    auto t = _pool.front().params;
    std::cout << t[0] << 's';*/
    /*std::string s = "in{qqq,aaa}do{q2,s,R}";
    boost::regex second_basic_expr{"(?<cmd1>(\\w+))(\\s)*"
                                           "{(?<opt1>((\\s)*(\\w)+,*(\\s)*)*)}"
                                           "\\s*(?<cmd2>(\\w+))(\\s)*"
                                           "{(?<opt2>((\\s)*(\\w)+,*(\\s)*)*)}"};
    boost::sregex_iterator itr(s.begin(), s.end(), second_basic_expr);
    boost::smatch sm;
    boost::regex_search(s, sm, second_basic_expr);
    std::cout << sm["cmd1"] << sm["cmd2"] << sm["opt1"] << sm["opt2"];*/
    belt_type b = {{0,"1"}, {1, "1"}, {2, "1"}, {3, "1"}, {4, "1"}};
    Turing::Belt belt(b);
    Turing::Handler hn(transitions_set(), belt, "", {});
    std::string obj = {     "in { 1, q1 } do { 1, q1, R }; \n"
                            "in { 0,q1 } do { 0, q1, R };\n"
                            "in { lambda, q1 } do { lambda, q2, L };\n"
                            "in { 1, q2 } do { 0, q2, L };\n"
                            "in { 0, q2 } do { 1, q3, L };\n"
                            "in { lambda, q2 } do { 1, qs, C };\n"
                            "in { 0, q3 } do { 0, q3, L };\n"
                            "in { 1, q3 } do { 1, q3, L };\n"
                            "in { lambda, q3 } do { lambda, qs, C };\n"
                            "set_begin { q1 };\n"
                            "set_end { qs };"};
    /*boost::regex second_basic_expr{"(?<cmd1>(\\w+))(\\s)*"
                                           "{(?<opt1>((\\s)*(\\w)+,*(\\s)*)*)}"
                                           "\\s*(?<cmd2>(\\w+))(\\s)*"
                                           "{(?<opt2>((\\s)*(\\w)+,*(\\s)*)*)}"};
    boost::regex parser{".*?;"};
    boost::sregex_iterator xIt(obj.begin(), obj.end(), parser);
    while (xIt != boost::sregex_iterator{}) {
        boost::smatch what;
        std::string s = xIt->str();
        boost::regex_search(s, what, second_basic_expr);
        std::string ss = what["cmd1"] + what["cmd2"];
        std::cout << ss;
        ++xIt;
    }*/
    TuringInterpreter intr;
    auto cmd = intr.Interpret(obj);
    hn.SetCommands(cmd);
    Turing::ResultCode code = Turing::NormalWork;
    while (code == Turing::NormalWork) {
        code = hn.OneStep();
    }
    return 0;
}

