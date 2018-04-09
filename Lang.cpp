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

void TuringInterpreter::TuringInterpreter() {
    key_word = new KeyWord;
    options = new Options;
}

TuringInterpreter::~TuringInterpreter() {
    delete key_word;
    delete options;
}

request_pool TuringInterpreter::Interpret(const std::string &candidate) {
    request_pool result;
    boost::regex basic_expr{"(?<command>(\\w+))(\\s)*{(?<options>((\\s)*(\\w)+,*(\\s)*)*)}"};
    boost::smatch what;
    if (boost::regex_search(candidate, what, basic_expr)) {
        key_word->configure_pool(what["command"], result);
        options->configure_pool(what["options"], result);
    }
    else
        throw InterpretException("Check basic grammar");
}

void KeyWord::configure_pool(const std::string &, request_pool &) {

}
