#pragma once
#include <string>
#include "calculate.hpp"
using std::string;
namespace bullpgia {
/* Chooser class. */
    class Chooser{

        public:
            /* Public pure virtual method. */
            virtual string choose(uint length) = 0;
    
    };
}