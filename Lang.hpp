#include "TM.hpp"

class KeyWord;
class Options;

class TuringRequest;
class InterpretException {
public:
    InterpretException();
    InterpretException(const std::string &);
    std::string what();
private:
    std::string exception_message;
};

using request_pool = std::queue<TuringRequest>;

class TuringInterpreter {
public:
    TuringInterpreter();
    request_pool Interpret(const std::string &);
    virtual ~TuringInterpreter();
protected:
    virtual void configure_pool(const std::string &, request_pool &);
private:
    std::string end_of_line();
    TuringInterpreter *key_word;
    TuringInterpreter *options;
};

class KeyWord : public TuringInterpreter {
public:
    KeyWord() : TuringInterpreter(){}
protected:
    void configure_pool(const std::string &, request_pool &);
};

class Options : public TuringInterpreter {
public:
    Options() : TuringInterpreter(){}
protected:
    void configure_pool(const std::string &, request_pool &);
};