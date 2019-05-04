#include "SmartGuesser.hpp"
using namespace bullpgia;

/* Default constructor. */
SmartGuesser::SmartGuesser(): numbers(10), perm(0){
    this->knownNumbers = 0;
    this->currentNum = 0;
    this->firstTime = true;
}

/* This method starts the game with input length. */
void SmartGuesser::startNewGame(uint length){
    string r = "";
    char c = '0';
	for (uint i = 0 ; i < length ; ++i) {
		r += c;
	}
	this->currGuess = r;
    
    /* INIT the data members. */
    for(int i = 0 ; i < 10 ; i++){
        this->numbers[i] = 0;
    }
    this->knownNumbers = 0;
    this->currentNum = 0;
    this->firstTime = true;
    this->perm.clear();
}

/* This method returns the current guess. */
string SmartGuesser::guess() {
    return this->currGuess;
}

/* 
 * This method recives the string that calculateBullAndPgia returns and learn about the next guess. 
 * It will choose an algorithm depending on length. 
 */
void SmartGuesser::learn(string reply){
    if(this->currGuess.length() < 5){
        this->shortAlgo(reply);
    }
    else{
        this->longAlgo(reply);
    }
}

void SmartGuesser::shortAlgo(string reply){
    int len = this->currGuess.length();
    /* First stage - finding known numbers. */
    if(knownNumbers < len && currentNum < 10){
        /* If current num doesnt exist in the chooser string. */
        if(reply == "0,0"){
            this->numbers[this->currentNum] = 0;
            this->currentNum++;
        }
        /* If current num exist in the chooser string. */
        else{
            this->numbers[this->currentNum] = 1;
            this->currentNum++;
            this->knownNumbers++;
        }
        string guess = "";
        char c = '0' + this->currentNum;
	    for (uint i = 0; i < len; ++i) {
		    guess += c;
	    }
        this->currGuess = guess;
    }
    /* Stage two - after finding the numbers in chooser string. */
    else{
        /* If first time. */
        if(this->firstTime){
            string theNumbers;
            /* Create a string of the numbers that in chooser. */
            for(int i = 0 ; i < 10 ; i++){
                if(this->numbers[i] == 1){
                    theNumbers += to_string(i);
                }
            }
            int start = pow(10,len);//starting index.
            int end = start *2; // ending index.
            string temp,tempNum;
            int counter = 0;
            bool flag = true;
            string strTheNumbers = theNumbers;
            /* Goes over all permutation */
            for(int i = start ; i < end ; i++){
                temp = to_string(i);
                temp = temp.substr(1);
                tempNum = temp;
                
                /* Checking if the number is a permutation that fill all the numbers in chooser string. */ 
                for(int j = 0 ; j < theNumbers.length() ; j++ ){
                    if(tempNum.find(strTheNumbers[j]) == -1 ){
                        flag = false;
                    }
                }
                /* If not a permutation continue. */
                if(flag == false){
                    flag = true;
                    continue;
                }

                /* Checking if the current permutation fill all the numbers of cooser string. */
                for(int j = 0 ;  j < theNumbers.length(); j++ ){
                    for(int l = 0 ; l < tempNum.length() ; l++){
                        if(theNumbers[j] == tempNum[l]){
                            tempNum[l] = 'x';
                        }
                    }
                }
                /* Count how many x'is in tempNum. */
                for(int j = 0 ; j < tempNum.length() ; j++){
                    if(tempNum[j] == 'x'){
                        counter++;
                    }
                }
                /* If the current permutation fill all the numbers of cooser string. */
                if(counter == tempNum.length()){
                    this->perm.push_back(temp);
                }
                counter = 0;
            }
            firstTime = false;
            if(this->perm.size() > 0){
                this->currGuess = this->perm[0];
                this->perm.erase(perm.begin()); 
            } 
        }
        else{
            if(this->perm.size() > 0){
                this->currGuess = this->perm[0];
                this->perm.erase(perm.begin()); 
            }
        }
        
    }
}

void SmartGuesser::longAlgo(string reply){
    
}
