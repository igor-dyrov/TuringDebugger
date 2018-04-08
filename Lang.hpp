#include "TM.hpp"

class KeyWord;
class Options;

class TuringInterpreter {
public:
    TuringInterpreter();
    virtual void interpret(std::string &);
protected:
private:
    TuringInterpreter *key_word;
    TuringInterpreter *options;
};

class KeyWord : public TuringInterpreter {

};

class Options : public TuringInterpreter {

};