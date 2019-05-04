/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#include "calculate.hpp"

#define COMMA ,

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i=0; i<1; ++i) {
			 testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=100, true);  // smarty should always win in at most 10 turns!
		}


	/* Our tests! */


	testcase.setname("Testing calculate bull and pgia")
	.CHECK_OUTPUT(calculateBullAndPgia("1","1"), "1,0")      // 1 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("1","7"), "0,0")      // 0 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("20","30"), "1,0")      // 1 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("55","15"), "1,0")      // 1 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("55","55"), "2,0")      // 2 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("14","41"), "0,2")      // 0 bull, 2 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("74","81"), "0,0")      // 0 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("456","564"), "0,3")      // 0 bull, 3 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("123","789"), "0,0")      // 0 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("123","123"), "3,0")      // 3 bull, 0 pgia

	.CHECK_OUTPUT(calculateBullAndPgia("555","115"), "1,0")      // 1 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("555","151"), "1,0")      // 1 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("555","511"), "1,0")      // 1 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("555","551"), "2,0")      // 2 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("555","555"), "3,0")      // 3 bull, 0 pgia

	.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("1234","7896"), "0,0")      // 0 bull, 0 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("12345", "15432"), "1,4")	// 1 bull, 4 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("12345", "12534"), "2,3")	// 2 bull, 3 pgia	
	.CHECK_OUTPUT(calculateBullAndPgia("12345", "12354"), "3,2")	// 3 bull, 2 pgia
	.CHECK_OUTPUT(calculateBullAndPgia("1234567","1234567"), "7,0")	// 7 bull, 0 pgia ---try long input
	.CHECK_OUTPUT(calculateBullAndPgia("987654321","987654321"), "9,0")	// 9 bull, 0 pgia  ---try long input

;
	/* Our Testing constant chooser/guesser" */
	ConstantChooser c4567{"4567"}, c1089{"1089"}, c4632{"4632"};
	ConstantGuesser g4567{"4567"}, g7852{"7852"}, g6378{"6378"};
	
	/* Spacial cases */
	ConstantChooser c0000{"0000"}, c0001{"0001"};
	testcase.setname("Testing constant chooser/guesser")


	.CHECK_EQUAL(play(c4567, g4567, 4, 100), 1)      // guesser wins in one turn.
	.CHECK_EQUAL(play(c4567, g4567, 3, 100),0)     //  illegal number 
	.CHECK_EQUAL(play(c4632, g6378, 4, 100), 101)    // guesser loses by running out of turns 
	.CHECK_EQUAL(play(c1089, g7852, 4, 100), 101)   // guesser loses by running out of turns
;

testcase.setname("Testing smart guesser");
	RandomChooser rand;
	SmartGuesser smart;
	

		/* ---------------------Checking input in length 4,3,2,1 ---------------------*/
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 4, 100)<=100, true);  // smarty should always win in at most 100 turns!
		}
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 4, 100)<=90, true);  // smarty should always win in at most 90 turns!
		}
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 4, 100)<=70, true);  // smarty should always win in at most 70 turns!
		}
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 4, 100)<=60, true);  // smarty should always win in at most 60 turns!
		}
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 4, 100)<=50, true);  // smarty should always win in at most 50 turns!
		}
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 3, 100)<=40, true);  // smarty should always win in at most 40 turns!
		}
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 2, 100)<=20, true);  // smarty should always win in at most 20 turns!
		}
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(rand, smart, 1, 100)<=10, true);  // smarty should always win in at most 10 turns!
		}
		/* ---------------------End of checking input in length 4,3,2,1 ---------------------*/

		// /* ---------------------Checking input in length 5 ---------------------*/
		// for (uint i=0; i<100; ++i) {
		// 	testcase.CHECK_EQUAL(play(rand, smart, 5, 100)<=100, true);  // smarty should always win in at most 10 turns!
		// }

		testcase.setname("Testing smart guesser with constant chooser")
		/* Testing smart guesser with constant chooser */
		.CHECK_EQUAL(play(c4567, smart, 4, 100)<=100, true)
		.CHECK_EQUAL(play(c1089, smart, 4, 100)<=100, true)
		.CHECK_EQUAL(play(c4632, smart, 4, 100)<=100, true)
		.CHECK_EQUAL(play(c1234, smart, 4, 100)<=100, true)
		// .CHECK_EQUAL(play(c12345, smart, 5, 100)<=100, true)
		.CHECK_EQUAL(play(c9999, smart, 4, 100)<=100, true)

		/* Checking for the spacial cases */
		.CHECK_EQUAL(play(c0000, smart, 4, 100)<=100, true) // checking "0000"
		.CHECK_EQUAL(play(c0001, smart, 4, 100)<=100, true) // // checking "0001"
	;




    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}

