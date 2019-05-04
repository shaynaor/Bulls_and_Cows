#pragma once
#include <string>
#include "calculate.hpp"
using std::string;

namespace bullpgia {
    /* Guesser class. */
    class Guesser{

        protected:
            uint length; // The length of the string.
       

        public:
            /*------ Public virtual method.------ */
            /* This method starts the game with input length. */
            virtual void startNewGame(uint length){this->length = length;}
            /* Pure virtual method -returns string- the guesser guess. */
            virtual string guess() = 0;
            /* This method recives the string that calculateBullAndPgia returns and learn about the next guess. */
            virtual void learn(string reply){}
    
    };
}