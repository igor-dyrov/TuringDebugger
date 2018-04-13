#include "Lang.hpp"

InterpretException::InterpretException() {
    exception_message = "blank message";
}

InterpretException::InterpretException(const std::string &value) {
    exception_message = value;
}

std::string InterpretException::what() {
    return exception_message;
}

TuringInterpreter::TuringInterpreter() {
    key_word = new KeyWord;
    options = new Options;
    has_ptrs = true;
}

TuringInterpreter::~TuringInterpreter() {
    if (has_ptrs) {
        delete key_word;
        delete options;
    }
    has_ptrs = false;
}

request_pool TuringInterpreter::Interpret(const std::string &candidate) {
    request_pool result;
    boost::regex first_basic_expr{"(?<command>(\\w+))(\\s)*{(?<options>((\\s)*(\\w)+,*(\\s)*)*)}"};
    boost::regex second_basic_expr{"(?<cmd1>(\\w+))(\\s)*"
                                            "{(?<opt1>((\\s)*(\\w)+,*(\\s)*)*)}"
                                            "\\s*(?<cmd2>(\\w+))(\\s)*"
                                            "{(?<opt2>((\\s)*(\\w)+,*(\\s)*)*)}"};
    boost::regex parser{".*?;"};
    boost::sregex_iterator xIt(candidate.begin(), candidate.end(), parser);
    while (xIt != boost::sregex_iterator{}){
        boost::smatch what;
        TuringRequest temp;
        std::string one_cmd = xIt->str();
        if  (boost::regex_search(one_cmd, what, second_basic_expr)) {
            std::string united_command = what["cmd1"] + what["cmd2"];
            std::string united_options = what["opt1"] + what["opt2"];
            key_word->get_request(united_command, temp);
            options->get_request(united_options, temp);
            result.push(temp);
        }
        else if (boost::regex_search(one_cmd, what, first_basic_expr)) {
            key_word->get_request(what["command"], temp);
            options->get_request(what["options"], temp);
            result.push(temp);
        }
        else
            throw InterpretException("Check basic construction grammar");
        ++xIt;
    }
    return result;
}

void KeyWord::get_request(const std::string &cmd, TuringRequest &request) {
    if (cmd == "set_begin")
        request.type_of_action = request.set_beg;
    else if(cmd == "set_end")
        request.type_of_action = request.set_end;
    else if (cmd == "indo")
        request.type_of_action = request.transition;
    else
        throw InterpretException("Bad command");
}

void Options::get_request(const std::string &opt, TuringRequest &request) {
    boost::regex param_expr{"\\w+"};
    boost::sregex_iterator itr(opt.begin(), opt.end(), param_expr);
    while (itr != boost::sregex_iterator{}) {
        request.params.push_back(itr->str());
        ++itr;
    }
}
