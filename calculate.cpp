#include "calculate.hpp"
/* This Function returns the number of bull and pgia by format "bull,pgia" */
string calculateBullAndPgia(string choice, string guess){

    int bullCounter = 0;
    /* Cuont how many bulls in the guess string. */
    for(int i = 0 ; i < choice.length() ; i++){
        if(choice[i] == guess[i]){
            bullCounter++;
            choice[i] = 'b';
            guess[i] = 'b';
        }
    }
    int pgiaCounter = 0;
    /* Cuont how many pgia in the guess string. */
    for(int i = 0 ; i < choice.length() ; i++){
        for(int j = 0 ; j < choice.length() ; j++){
            if(choice[j] == guess[i] && choice[j] != 'b' && choice[j] != 'p'){
                pgiaCounter++;
                choice[j] = 'p';
            }
        }
    }
    return to_string(bullCounter) + "," + to_string(pgiaCounter);
}