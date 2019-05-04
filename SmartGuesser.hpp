#pragma once
#include "Guesser.hpp"
#include <vector> 
#include <math.h>
using std::string;
/* SmartGuesser class - smart gusser will guess the chooser code fast */
class SmartGuesser: public bullpgia::Guesser {
    /* Private data members */
    private:
        string currGuess;//Current smartGuesser guess.
        std::vector<int> numbers;//The vector in position i is 1 iff i in chooser string.
        int knownNumbers; //The number of diffrent numbers in chooser string.
        int currentNum; 
        bool firstTime; // flag
        std::vector<string> perm; // all permutation of the numbers in chooser string.
        
        /* Private functions*/
        void shortAlgo(string reply);
        void longAlgo(string reply);

    public:
        SmartGuesser();
        /* This method starts the game with input length. */
        virtual void startNewGame(uint length)override;
        /* This method returns the current guess. */
        virtual string guess() override;
        /* This method recives the string that calculateBullAndPgia returns and learn about the next guess. */
        virtual void learn(string reply)override;
        


};

