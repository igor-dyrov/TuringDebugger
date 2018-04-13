#include "settings.hpp"

class KeyWord;
class Options;

struct TuringRequest {
    enum Command {set_beg, set_end, transition} type_of_action;
    std::vector<std::string> params;
};

class InterpretException {
public:
    InterpretException();
    InterpretException(const std::string &);
    std::string what();
private:
    std::string exception_message;
};

class TuringInterpreter {
public:
    TuringInterpreter();
    TuringInterpreter(int){has_ptrs = false;};
    request_pool Interpret(const std::string &);
    virtual ~TuringInterpreter();
protected:
    virtual void get_request(const std::string &, TuringRequest &){}
private:
    bool has_ptrs;
    TuringInterpreter *key_word;
    TuringInterpreter *options;
};

class KeyWord : public TuringInterpreter {
public:
    KeyWord() : TuringInterpreter(1){}
protected:
    void get_request(const std::string &, TuringRequest &);
};

class Options : public TuringInterpreter {
public:
    Options() : TuringInterpreter(1){}
protected:
    void get_request(const std::string &, TuringRequest &);
};
