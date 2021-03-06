/* 
test_roman_calc.c

Andrew Howard - 2016

Program used to test functions of the Roman numeral calculator library, libromancalc.  

This program uses the Check library, libcheck, to run a series of tests on the functions for conversion, addition, and subtraction.  

*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <check.h>

#include "roman_numeral_calc.h"

//Test for the decimal to Roman numeral conversion function.  
START_TEST(convert_decimal_to_roman_test) {

	//Allocate the C string "numeral" to store the results of the 
	//conversion function.  
	char * numeral = allocate_roman_numeral_string();

	//Check that the conversion function returns the correct 
	//flag when valid and invalid input is provided.   
	int failure_flag;
	
	//Correct input, failure_flag should equal 0.
	failure_flag = convert_decimal_to_roman(1, numeral);
	ck_assert_int_eq(failure_flag, 0);

	//Incorrect inputs, failure_flag should equal 1.  
	failure_flag = convert_decimal_to_roman(0, numeral);
	ck_assert_int_eq(failure_flag, 1);

	failure_flag = convert_decimal_to_roman(4000, numeral);
	ck_assert_int_eq(failure_flag, 1);

	failure_flag = convert_decimal_to_roman(1, NULL);
	ck_assert_int_eq(failure_flag, 1);

	//Check various conversions from decimal to Roman numerals.

	//1 -> I
	convert_decimal_to_roman(1, numeral);
	ck_assert_str_eq(numeral, "I");
	
	//3 -> III
	convert_decimal_to_roman(3, numeral);
	ck_assert_str_eq(numeral, "III");

	//4 -> IV
	convert_decimal_to_roman(4, numeral);
	ck_assert_str_eq(numeral, "IV");
	
	//5 -> V
	convert_decimal_to_roman(5, numeral);
	ck_assert_str_eq(numeral, "V");
	
	//9 -> IX
	convert_decimal_to_roman(9, numeral);
	ck_assert_str_eq(numeral, "IX");
	
	//10 -> X
	convert_decimal_to_roman(10, numeral);
	ck_assert_str_eq(numeral, "X");
	
	//30 -> XXX
	convert_decimal_to_roman(30, numeral);
	ck_assert_str_eq(numeral, "XXX");
	
	//40 -> XL
	convert_decimal_to_roman(40, numeral);
	ck_assert_str_eq(numeral, "XL");
	
	//50 -> L
	convert_decimal_to_roman(50, numeral);
	ck_assert_str_eq(numeral, "L");
	
	//80 -> LXXX
	convert_decimal_to_roman(80, numeral);
	ck_assert_str_eq(numeral, "LXXX");
	
	//100 -> C
	convert_decimal_to_roman(100, numeral);
	ck_assert_str_eq(numeral, "C");
	
	//287 -> CCLXXXVII
	convert_decimal_to_roman(287, numeral);
	ck_assert_str_eq(numeral, "CCLXXXVII");
	
	//288 -> CCLXXXVIII
	convert_decimal_to_roman(288, numeral);
	ck_assert_str_eq(numeral, "CCLXXXVIII");
	
	//300 -> CCC
	convert_decimal_to_roman(300, numeral);
	ck_assert_str_eq(numeral, "CCC");
	
	//400 -> CD
	convert_decimal_to_roman(400, numeral);
	ck_assert_str_eq(numeral, "CD");
	
	//500 -> D
	convert_decimal_to_roman(500, numeral);
	ck_assert_str_eq(numeral, "D");
	
	//800 -> DCCC
	convert_decimal_to_roman(800, numeral);
	ck_assert_str_eq(numeral, "DCCC");

	//1000 -> M
	convert_decimal_to_roman(1000, numeral);
	ck_assert_str_eq(numeral, "M");

	//3000 -> MMM
	convert_decimal_to_roman(3000, numeral);
	ck_assert_str_eq(numeral, "MMM");

	//900 -> CM
	convert_decimal_to_roman(900, numeral);
	ck_assert_str_eq(numeral, "CM");

	//2900 -> MMCM
	convert_decimal_to_roman(2900, numeral);
	ck_assert_str_eq(numeral, "MMCM");

	//Free memory assigned to "numeral" string.
	free(numeral);
}
END_TEST

//Test for the Roman numeral to decimal conversion function.  
START_TEST(convert_roman_to_decimal_test) {

	//integer to store the returned converted number
	int decimal = 0;
	
	//Check various conversions from Roman numeral to decimal.  
	
	//I -> 1
	convert_roman_to_decimal("I", &decimal);
	ck_assert_int_eq(decimal, 1);
	
	//III -> 3
	convert_roman_to_decimal("III", &decimal);
	ck_assert_int_eq(decimal, 3);
	
	//IV -> 4
	convert_roman_to_decimal("IV", &decimal);
	ck_assert_int_eq(decimal, 4);
	
	//V -> 5
	convert_roman_to_decimal("V", &decimal);
	ck_assert_int_eq(decimal, 5);
	
	//VIII -> 8
	convert_roman_to_decimal("VIII", &decimal);
	ck_assert_int_eq(decimal, 8);
	
	//IX -> 9
	convert_roman_to_decimal("IX", &decimal);
	ck_assert_int_eq(decimal, 9);
	
	//X -> 10
	convert_roman_to_decimal("X", &decimal);
	ck_assert_int_eq(decimal, 10);
	
	//XXX -> 30
	convert_roman_to_decimal("XXX", &decimal);
	ck_assert_int_eq(decimal, 30);
	
	//XL -> 40
	convert_roman_to_decimal("XL", &decimal);
	ck_assert_int_eq(decimal, 40);
	
	//L -> 50
	convert_roman_to_decimal("L", &decimal);
	ck_assert_int_eq(decimal, 50);
	
	//LXXX -> 80
	convert_roman_to_decimal("LXXX", &decimal);
	ck_assert_int_eq(decimal, 80);
	
	//XC -> 90
	convert_roman_to_decimal("XC", &decimal);
	ck_assert_int_eq(decimal, 90);
	
	//C -> 100
	convert_roman_to_decimal("C", &decimal);
	ck_assert_int_eq(decimal, 100);
	
	//CCC -> 300
	convert_roman_to_decimal("CCC", &decimal);
	ck_assert_int_eq(decimal, 300);
	
	//CCLXXXVII -> 287
	convert_roman_to_decimal("CCLXXXVII", &decimal);
	ck_assert_int_eq(decimal, 287);
	
	//CCLXXXVIII -> 288
	convert_roman_to_decimal("CCLXXXVIII", &decimal);
	ck_assert_int_eq(decimal, 288);
	
	//CD -> 400
	convert_roman_to_decimal("CD", &decimal);
	ck_assert_int_eq(decimal, 400);
	
	//D -> 500
	convert_roman_to_decimal("D", &decimal);
	ck_assert_int_eq(decimal, 500);
	
	//DCCC -> 800
	convert_roman_to_decimal("DCCC", &decimal);
	ck_assert_int_eq(decimal, 800);
	
	//CM -> 900
	convert_roman_to_decimal("CM", &decimal);
	ck_assert_int_eq(decimal, 900);
	
	//M -> 1000
	convert_roman_to_decimal("M", &decimal);
	ck_assert_int_eq(decimal, 1000);
	
	//MCM -> 1900
	convert_roman_to_decimal("MCM", &decimal);
	ck_assert_int_eq(decimal, 1900);
	
	//MMCM -> 2900
	convert_roman_to_decimal("MMCM", &decimal);
	ck_assert_int_eq(decimal, 2900);
	
	//MMM -> 3000
	convert_roman_to_decimal("MMM", &decimal);
	ck_assert_int_eq(decimal, 3000);
	
	//MMMCM -> 3900
	convert_roman_to_decimal("MMMCM", &decimal);
	ck_assert_int_eq(decimal, 3900);
	
	//Test if conversion function properly handles invalid inputs.
	int failure_flag = 0;
	
	//Correct input, failure_flag should equal 0.  
	failure_flag = convert_roman_to_decimal("MMMCM", &decimal);
	ck_assert_int_eq(failure_flag, 0);
	
	//Incorrect inputs, failure_flag should equal 1.
	failure_flag = convert_roman_to_decimal("MMMIICM", &decimal);
	ck_assert_int_eq(failure_flag, 1);
	
	failure_flag = convert_roman_to_decimal("IIII", &decimal);
	ck_assert_int_eq(failure_flag, 1);
	
	failure_flag = convert_roman_to_decimal("IVI", &decimal);
	ck_assert_int_eq(failure_flag, 1);
	
	failure_flag = convert_roman_to_decimal("absC", &decimal);
	ck_assert_int_eq(failure_flag, 1);

	failure_flag = convert_roman_to_decimal(NULL, &decimal);
	ck_assert_int_eq(failure_flag, 1);
	
	failure_flag = convert_roman_to_decimal("IV", NULL);
	ck_assert_int_eq(failure_flag, 1);	
}
END_TEST

/* Test both the convert_decimal_to_roman() and convert_roman_to_decimal() functions 
by converting all integers 1-3999 to Roman numerals, then back to 
decimal, and then comparing the results to the inputs. */
START_TEST(double_conversion_test) {

	//Roman numeral and decimal variables used in double conversion.
	char * numeral = allocate_roman_numeral_string();
	int decimal;
	
	int failure_flag = 0;

	//Check every integer from 1-3999.
	for(int i=1; i <= MAX_DECIMAL; i++) {
	
		//Convert decimal to Roman numeral, check for failure.  
		failure_flag = convert_decimal_to_roman(i, numeral);
		ck_assert_msg(failure_flag == 0, "Failed to convert %i to Roman numeral.", i);
		
		//Convert Roman numeral decimal, check for failure.  
		failure_flag = convert_roman_to_decimal(numeral, &decimal);
		//ck_assert_int_eq(failure_flag, 0);
		ck_assert_msg(failure_flag == 0, "Failed to convert %s (%i) to decimal number.", numeral, i);
		
		//The initial number 'i' should equal 'decimal'.
		ck_assert_int_eq(decimal, i);
	}
	
	//Free memory of string.  
	free(numeral);
}
END_TEST

/* Test the roman_addition() function.  Whole numbers that sum up to 
anywhere within 2-3999 are converted to Roman numerals, those are 
passed to the addition function, the resulting roman numeral is 
converted back to decimal, and the result is compared.  Thorough 
testing of the conversion functions allows us to conduct this test 
with confidence.  */
START_TEST(roman_addition_test) {

	//Strings used for Roman numeral addition
	char * numeral_a = allocate_roman_numeral_string();
	char * numeral_b = allocate_roman_numeral_string();
	char * numeral_sum = allocate_roman_numeral_string();
	
	//Integers for decimal addition
	int decimal_a;
	int decimal_b;
	int decimal_sum;
	
	//Flag to check for failure condition from roman_addition()
	int failure_flag = 0;
	
	//Set seed for random number generator.  
	srand(time(NULL));
	
	//Try many random values for a and b that sum up to less than 
	//3999. Initial idea to test all whole numbers that sum to 3999 
	//resulted in a timeout error with the libcheck function.  
	for(int i=0; i<10000; i++) {

		//Sum a+b is between 1-3999
		decimal_a = (rand() % (MAX_DECIMAL-1)) + 1;
		decimal_b = (rand() % (MAX_DECIMAL-decimal_a)) + 1;
		
		convert_decimal_to_roman(decimal_a, numeral_a);
		convert_decimal_to_roman(decimal_b, numeral_b);
	
		//Add Roman numerals, check flag for failure.  
		failure_flag = roman_addition(numeral_a, numeral_b, numeral_sum);
		ck_assert_int_eq(failure_flag, 0);
	
		convert_roman_to_decimal(numeral_sum, &decimal_sum);

		//Compare the result to the inputs.  
		ck_assert_int_eq(decimal_sum, (decimal_a + decimal_b));
	}
}
END_TEST

/* Test the roman_subtraction() function.  Whole numbers that have a 
difference anywhere within 2-3998 are converted to Roman numerals, 
those are passed to the subtraction function, the resulting roman 
numeral is converted back to decimal, and the result is compared.  
Thorough testing of the conversion functions allows us to conduct this 
test with confidence.  */
START_TEST(roman_subtraction_test) {

	//Strings used for Roman numeral subtraction
	char * numeral_a = allocate_roman_numeral_string();
	char * numeral_b = allocate_roman_numeral_string();
	char * numeral_diff = allocate_roman_numeral_string();

	//Integers for decimal subtraction
	int decimal_a;
	int decimal_b;
	int decimal_sum;
	
	//Flag to check for failure condition from roman_subtraction()
	int failure_flag = 0;
	
	//Set seed for random number generator.  
	srand(time(NULL));
	
	//Try many random values for a and b that have a difference 
	//greater than 1.  
	for(int i=0; i<10000; i++) {

		//Difference a-b is between 1-3998		
		decimal_a = (rand() % (MAX_DECIMAL-1)) + 2; //2 to 3999
		decimal_b = (rand() % (decimal_a-1)) + 1; //1 to (a-1)

		convert_decimal_to_roman(decimal_a, numeral_a);
		convert_decimal_to_roman(decimal_b, numeral_b);
	
		//Subtract Roman numerals, check flag for failure.  
		failure_flag = roman_subtraction(numeral_a, numeral_b, numeral_diff);
		ck_assert_int_eq(failure_flag, 0);
	
		convert_roman_to_decimal(numeral_diff, &decimal_sum);

		//Compare the result to the inputs.  
		ck_assert_int_eq(decimal_sum, (decimal_a - decimal_b));
	}
}
END_TEST

/* This function creates the test Suite structure, with the test cases 
added to it.  The test suite is then run within the main function.  */
static Suite *create_test_suite(void) {

	//Suite struct
	Suite *s;

	//test case struct
	TCase *tc_core;

	//Initialize the test suite. 
	s = suite_create("Roman Calc Test Suite");

	//Create a single test case that consits of several tests of the 
	//Roman numeral calculator's functions.  
	tc_core = tcase_create("Core");

	//Add the test for decimal to Roman conversion to the test case.  
	tcase_add_test(tc_core, convert_decimal_to_roman_test);
	
	//Add the test for Roman to decimal conversion to the test case.  
	tcase_add_test(tc_core, convert_roman_to_decimal_test);

	//Add the test for double conversion, an broad test of both conversion functions.  
	tcase_add_test(tc_core, double_conversion_test);
	
	//Add the test for the addition function.  
	tcase_add_test(tc_core, roman_addition_test);
	
	//Add the test for the subtraction function.
	tcase_add_test(tc_core, roman_subtraction_test);

	//Add the test case to the tese suite.  
	suite_add_tcase(s, tc_core);

	//Return the finished test suite.  
	return s;
}

/* As a test program, the main function will simply run the test 
suite, which consists of a main test case and the tests for the 
calculator's functions.  */
int main(void) {

	//Count the number of tests failed.  
	int number_failed;

	//Structs for test suite and suite runner
	Suite *s;
	SRunner *sr;

	//Create the test suite.  
	s = create_test_suite();

	//Create the runner for the test suite. 
	sr = srunner_create(s);

	//Run all tests of the test suite.  
	srunner_run_all(sr, CK_NORMAL);

	//Count the number of tests that failed.  
	number_failed = srunner_ntests_failed(sr);

	//Delete the suite runner.  
	srunner_free(sr);

	//The program will exit with a failure if a test fails.  
	return(number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
