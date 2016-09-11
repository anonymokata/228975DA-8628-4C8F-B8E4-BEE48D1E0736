/* 
test_roman_calc.c

Andrew Howard - 2016

Program used to test functions of the Roman numeral calculator library, libromancalc.  
This program uses the Check library, libcheck, to run a series of tests on the 
functions for conversion, addition, and subtraction.  

*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "roman_numeral_calc.h"

//Test for the decimal to Roman numeral conversion function.  
START_TEST(convert_decimal_to_roman_test) {

	//Allocate the C string "numeral" to store the results of the 
	//conversion function.  
	char * numeral = (char*)malloc(sizeof(char) * (strlen(MAX_ROMAN)+1));
	memset(numeral, 0, strlen(MAX_ROMAN)+1);


	//Check that the conversion function returns the correct flag when proper and improper input is provided.  
	
	//correct input
	int flag = decimal_to_roman(1, numeral);
	ck_assert_int_eq(flag, 0);

	//incorrect inputs
	flag = decimal_to_roman(0, numeral);
	ck_assert_int_eq(flag, 1);

	flag = decimal_to_roman(4000, numeral);
	ck_assert_int_eq(flag, 1);

	flag = decimal_to_roman(1, NULL);
	ck_assert_int_eq(flag, 1);


	//Check if various conversions from decimal to Roman numerals work.

	//1 -> I
	decimal_to_roman(1, numeral);
	ck_assert_str_eq(numeral, "I");
	
	//3 -> III
	decimal_to_roman(3, numeral);
	ck_assert_str_eq(numeral, "III");

	//4 -> IV
	decimal_to_roman(4, numeral);
	ck_assert_str_eq(numeral, "IV");
	
	//5 -> V
	decimal_to_roman(5, numeral);
	ck_assert_str_eq(numeral, "V");
	
	//9 -> IX
	decimal_to_roman(9, numeral);
	ck_assert_str_eq(numeral, "IX");
	
	//10 -> X
	decimal_to_roman(10, numeral);
	ck_assert_str_eq(numeral, "X");
	
	//30 -> XXX
	decimal_to_roman(30, numeral);
	ck_assert_str_eq(numeral, "XXX");
	
	//40 -> XL
	decimal_to_roman(40, numeral);
	ck_assert_str_eq(numeral, "XL");
	
	//50 -> L
	decimal_to_roman(50, numeral);
	ck_assert_str_eq(numeral, "L");
	
	//80 -> LXXX
	decimal_to_roman(80, numeral);
	ck_assert_str_eq(numeral, "LXXX");
	
	//100 -> C
	decimal_to_roman(100, numeral);
	ck_assert_str_eq(numeral, "C");
	
	//300 -> CCC
	decimal_to_roman(300, numeral);
	ck_assert_str_eq(numeral, "CCC");
	
	//400 -> CD
	decimal_to_roman(400, numeral);
	ck_assert_str_eq(numeral, "CD");
	
	//500 -> D
	decimal_to_roman(500, numeral);
	ck_assert_str_eq(numeral, "D");
	
	//800 -> DCCC
	decimal_to_roman(800, numeral);
	ck_assert_str_eq(numeral, "DCCC");

	//1000 -> M
	decimal_to_roman(1000, numeral);
	ck_assert_str_eq(numeral, "M");

	//3000 -> MMM
	decimal_to_roman(3000, numeral);
	ck_assert_str_eq(numeral, "MMM");

	//900 -> CM
	decimal_to_roman(900, numeral);
	ck_assert_str_eq(numeral, "CM");

	//2900 -> MMCM
	decimal_to_roman(2900, numeral);
	ck_assert_str_eq(numeral, "MMCM");


	//Free memory assigned to "numeral"
	free(numeral);
}
END_TEST

//Test for the Roman numeral to decimal conversion function.  
START_TEST(convert_roman_to_decimal_test) {

	//integer to store the returned converted number
	int decimal = 0;
	
	//Check if various conversions from Roman numerals to decimal 
	//numbers work.
	
	//I -> 1
	roman_to_decimal("I", &decimal);
	ck_assert_int_eq(decimal, 1);
	
	//IV -> 4
	roman_to_decimal("IV", &decimal);
	ck_assert_int_eq(decimal, 4);
	
	//CM -> 900
	roman_to_decimal("CM", &decimal);
	ck_assert_int_eq(decimal, 900);
	
	//M -> 1000
	roman_to_decimal("M", &decimal);
	ck_assert_int_eq(decimal, 1000);
	
	//MCM -> 1900
	int flag = roman_to_decimal("MCM", &decimal);
	ck_assert_int_eq(flag,0);
	
	ck_assert_int_eq(decimal, 1900);
	
	
	
	//MMCM -> 2900
	flag = roman_to_decimal("MMCM", &decimal);
	ck_assert_int_eq(flag,0);
	ck_assert_int_eq(decimal, 2900);
	
	//MMM -> 3000
	roman_to_decimal("MMM", &decimal);
	ck_assert_int_eq(decimal, 3000);
	
	//MMMCM -> 3900
	roman_to_decimal("MMMCM", &decimal);
	ck_assert_int_eq(decimal, 3900);
	
}
END_TEST

/* This function creates the test Suite structure, with the test cases added to it.  
The test suite is then run within the main function.  */
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

	//Add the test case to the tese suite.  
	suite_add_tcase(s, tc_core);

	//Return the finished test suite.  
	return s;
}

/* As a test program, the main function will simply run the test suite, which consists of a main test case and the small tests for the calculator's functions.  */
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
