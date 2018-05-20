#ifndef __SETTINGS__
#define __SETTINGS__

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <queue>
#include <boost/regex.hpp>
#include <stack>

class TuringRequest;

namespace Turing {
    struct Situation;
    struct Command;
}

using symbol = std::string;
using state = std::string;
using belt_type = std::map<int, symbol>;
using request_pool = std::queue<TuringRequest>;
using transitions_set = std::map<Turing::Situation, Turing::Command>;

#endif
