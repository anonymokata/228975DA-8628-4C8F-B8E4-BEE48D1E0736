/*
roman_numeral_calc.c

Andrew Howard - 2016 

This file defines library functions that allow the user to add and subtract Roman numeral numbers.  Other functions facilitate the conversion between Roman numerals and decimal numbers.  The largest Roman numeral supported is 3999 (MMMCMXCIX) and the smallest is 1 (I).  

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#include "roman_numeral_calc.h"

//Roman numeral symbols and associated decimal values.  These are used 
//in the conversion between decimal numbers and Roman numerals.  
static const char roman_symbol[] = {'M','D','C','L','X','V','I'};
static const int decimal_symbol[] = {1000, 500, 100, 50, 10, 5, 1};
static const int num_symbol = 7;

/* Convert decimal numbers to Roman numerals.  See header file for full description. */
int convert_decimal_to_roman(const int decimal, char * numeral) {

	//First check if number is within the accepted range. 
	if(decimal < MIN_DECIMAL || decimal > MAX_DECIMAL) {
		//Failed, return.  
		return 1;
	}

	//Check for a null pointer on numeral string.  
	if(numeral == NULL) {
		//Failed, return.  
		return 1;
	}

	//Ensure the numeral string is clean before writing over it.  
	memset(numeral, 0, strlen(numeral));

	//Generate buffer string used when generating Roman numerals.  
	char * buffer = allocate_roman_numeral_string();

	//Temporary integer to store value of remaining decimal number 
	//as Roman numerals are added to the string.  
	int decimal_temp = decimal;

	/* When converting from decimal to Roman numerals, there are four 
	sections within each decimal place (powers of 10) that are 
	represented different by numerals.  
	
	i) Immediately less the higher power of 10 (i.e. 9 -> IX)
	ii) Less than the highest number but not less than the middle 
		value. (i.e. 8 -> VIII)
	iii) Immediately less than the middle value.  (i.e. 4 -> IV)
	iv) Lowest values (i.e. 2 -> II)
	
	The rules for converting decimal numbers to Roman numerals can be 
	applied systematically to each decimal place, so long as these 
	four regions are processed accordingly for the respective Roman 
	numeral values.  
	*/

	//As the largest decimal number allowed is 3999, only the lowest 
	//region of the 1000's place is checked.  This is a special case.
	if(decimal_temp >= 1000) {

		//Count the whole 1000's in the decimal number.   
		int whole_count = floor(((float)decimal_temp)/1000.0);

		//Add 1000's by appending "M" several times.  Maximum of 3. 
		for(int i=0; i<whole_count; i++) {

			//Append "M" to end of numeral buffer string.
			strcat(buffer,"M");

			decimal_temp -= 1000;
		}
	}
	
	//For each decimal place from the 100's to the 1's, convert to 
	//Roman numerals.  "symbol_iter" starts at 2 because that is the 
	//index for the 100s decimal value and Roman numeral symbol C.  
	for(int symbol_iter=2; symbol_iter < num_symbol; symbol_iter+=2) {
	
		//decimal value that represents the decimal place
		int decimal_place_value = decimal_symbol[symbol_iter];
	
		//Decimal number values representing the four cases of values 
		//within the current decimal place.  
		int value_nine = 9 * decimal_place_value;
		int value_five = 5 * decimal_place_value;
		int value_four = 4 * decimal_place_value;
		int value_one = decimal_place_value;
		
		if(decimal_temp >= value_nine) {

			//Append the Roman numeral for the value immediately 
			//before the next highest decimal place.  That is, "CM", 
			//"XC", or "IX".  
			buffer[strlen(buffer)] = roman_symbol[symbol_iter];
			buffer[strlen(buffer)] = roman_symbol[symbol_iter-2];

			decimal_temp -= value_nine;
		}
	
		//Check if decimal_temp contains the middle value for the 
		//current decimal place.   
		if(decimal_temp >= value_five) {
	
			//Append Roman numeral for middle value to buffer.
			buffer[strlen(buffer)] = roman_symbol[symbol_iter-1];
 
			decimal_temp -= value_five;
		}
	
		//Check if decimal_temp is immediately less than the middle 
		//value. 
		if(decimal_temp >= value_four) {
		
			//Append Roman numerals for the value immediately less 
			//than the middle value.  (i.e. IV)
			buffer[strlen(buffer)] = roman_symbol[symbol_iter];
			buffer[strlen(buffer)] = roman_symbol[symbol_iter-1];

			decimal_temp -= value_four;
		}
	
		//Check decimal_temp for value in the lowest portion of the 
		//current decimal place.  
		if(decimal_temp >= value_one) {
	
			//Count the whole multiples of value_one in decimal_temp. 
			int whole_count = floor(((float)decimal_temp)/((float)value_one));

			//Add numeral for current decimal place.  Maximum of 3. 
			for(int i=0; i<whole_count; i++) {

				//Append numeral for current decimal place to end of 
				//numeral buffer string.
				buffer[strlen(buffer)] = roman_symbol[symbol_iter];

				decimal_temp -= value_one;
			}
		}
	}

	//Copy contents of buffer to "numeral". 
	strncpy(numeral, buffer, strlen(buffer)+1);

	//decimal_temp should equal zero now, with all value extracted 
	//and converted to Roman numerals.  If not, something went 
	//wrong.  
	if(decimal_temp != 0) {
		//Failed, return.  
		return 1;
	}

	//Free buffer memory
	free(buffer);

	//Successful conversion, return success flag value.  
	return 0;
}

/* Convert Roman numerals to decimal numbers.  See header file for full description. */
int convert_roman_to_decimal(const char * numeral, int * decimal) {

	//Ensure pointers are not null.  
	if(numeral == NULL || decimal == NULL) {
		//Invalid input, conversion fails.  
		return 1;
	}

	//temporary variable to store decimal number as it is built up 
	int decimal_temp = 0;
	
	//Copy the original numeral to another c string that can be 
	//manipulated as need.  
	char * ntemp = (char*)malloc(sizeof(char) * (strlen(numeral)+1));
	memcpy(ntemp, numeral, strlen(numeral)+1);
	
	//Ensure that the characters of the input string are valid.  
	//Lowercase correct letters are accepted and converted to 
	//uppercase.  
	for(int i=0; i<strlen(ntemp); i++) {
		
		//Force conversion to uppercase.
		ntemp[i] = toupper(ntemp[i]);
		
		//Checks if the letter is one of the accepted Roman symbols.
		if(ntemp[i] < 'C' || ntemp[i] > 'X') {
			
			//Invalid Roman numeral, exit.  
			free(ntemp);
			return 1;
		}
		else {
		
			//Check character against list of Roman symbols.  While 
			//this is a double-nested loop, both loops are small. 
			bool validChar = false;
			for(int j=0; j<num_symbol; j++) {
			
				if(ntemp[i] == roman_symbol[j]) {
					//Found valid character, exit loop.  
					validChar = true;
					break;
				}
			}
			
			//Current character in string is not a valid Roman numeral 
			//symbol.  Return a "1" for conversion failure.  
			if(!validChar) {
			
				free(ntemp);
				return 1;
			}
		}
	}
	 
	//If the numeral string is preceeded by M's, these represent 
	//values of 1000.  There should be 3 maximum.  
	int count=0;
	while(strchr(ntemp,'M') == ntemp) {
	
		//Add 1000 to decimal value.  
		decimal_temp += 1000;
		
		//Shift the characters of the string so the first is 
		//dropped off.  The null terminating character is copied 
		//over as well, so the string's length is correctly 
		//shortened.  
		memmove(ntemp, ntemp+1, strlen(ntemp));
		
		count++;
		
		//Check for more than 3 M's in a row.    
		if(count > 3) {
		
			//Incorrectly formated Roman numeral, return. 
			free(ntemp);
			return 1;
		}
	}
	
	/* Converting from Roman numerals to decimal numbers follows a 
	similar approach as the reverse conversion that is described in 
	"convert_decimal_to_roman()" above.  Within each decimal place, strings 
	representing 9, 5, 4, and 1 are searched for within "ntemp".  As 
	they are identified in leading positions in the numeral string, 
	they are removed from the front of the string and their equivalent 
	value is added to the growing decimal value, stored in "decimal_temp".  
	*/
	
	//For each decimal place from the 100's to the 1's, search for the 
	//Roman numerals that represent the respective values of 9, 5, 4, 
	//and 1.  "symbol_iter" starts at 2 because that is the 
	//index for the 100s decimal value and Roman numeral symbol C.  
	for(int symbol_iter=2; symbol_iter < num_symbol; symbol_iter+=2) {
	
		//decimal value that represents the decimal place
		int dplace = decimal_symbol[symbol_iter];
	
		//Decimal number values representing the four cases of values 
		//within the current decimal place.  
		int val9 = 9 * dplace;
		int val5 = 5 * dplace;
		int val4 = 4 * dplace;
		int val1 = dplace;
	
		//Roman numeral strings that correspond to the above decimal 
		//values.  All are null-terimated c strings.  
		char numstr9[] = {'\0', '\0', '\0'};
		numstr9[0] = roman_symbol[symbol_iter];
		numstr9[1] = roman_symbol[symbol_iter-2];
		
		char numstr5[] = {'\0', '\0'};
		numstr5[0] = roman_symbol[symbol_iter-1];
		
		char numstr4[] = {'\0', '\0', '\0'};
		numstr4[0] = roman_symbol[symbol_iter];
		numstr4[1] = roman_symbol[symbol_iter-1];
		
		char numstr1[] = {'\0', '\0'};
		numstr1[0] = roman_symbol[symbol_iter];
	
		//Check for numeral string that represents the 9 value.   	
		if(strstr(ntemp, numstr9)) {
	
			//Check if the string is at beginning.  
			if(strstr(ntemp, numstr9) == ntemp) {
		
				//Add the corresponding 9 value to the decimal.
				decimal_temp += val9;
		
				//Remove beginning two characters of string.  
				memmove(ntemp, ntemp+1, strlen(ntemp));
				memmove(ntemp, ntemp+1, strlen(ntemp));
			}
			else {
				//Incorrectly formated Roman numeral, return. 
				free(ntemp);
				return 1;
			}
		}
	
		//Check for numeral for 5, not necessarily at the beginning.  
		if(strstr(ntemp, numstr5)) {
	
			//Check for leading 5 numeral.  
			if(strstr(ntemp, numstr5) == ntemp) {
		
				//Add the corresponding 5 value to the decimal. 
				decimal_temp += val5;
		
				//Shift the characters of the string so the first is 
				//dropped off.  The null terminating character is 
				//copied over as well, so the string's length is 
				//correctly shortened.  
				memmove(ntemp, ntemp+1, strlen(ntemp));
			}
			else if(strstr(ntemp, numstr4) == ntemp) {
				//Check for leading numeral for 4 value.  
			
				//Add corresponding 4 value to the decimal.   
				decimal_temp += val4;
		
				//Shift the characters of the string so the first two 
				//are dropped off.  The null terminating character is 
				//copied twice over as well, so the string's length is 
				//correctly shortened.  
				memmove(ntemp, ntemp+1, strlen(ntemp));
				memmove(ntemp, ntemp+1, strlen(ntemp));
			
				//With leading numeral for 4 value, there should be no 
				//following numerals for the 1 value.  
				if(strstr(ntemp,"numstr1")) {
			
					//Incorrectly formated Roman numeral, return. 
					free(ntemp);
					return 1;
				}
			}
			else {
			
				//Incorrectly formated Roman numeral, return. 
				free(ntemp);
				return 1;
			}
		}
	
		//If the string starts with numerals for the 1 value, here 
		//should be 3 maximum.  
		int count=0;
		while(strstr(ntemp, numstr1) == ntemp) {
	
			//Add corresponding 1 value to the decimal. 
			decimal_temp += val1;
		
			//Shift the characters of the string so the first is 
			//dropped off.  The null terminating character is copied 
			//over as well, so the string's length is correctly 
			//shortened.  
			memmove(ntemp, ntemp+1, strlen(ntemp));
		
			count++;
		
			//Check for more than 3 numerals for 1 values in a row.    
			if(count > 3) {
		
				//Incorrectly formated Roman numeral, return. 
				free(ntemp);
				return 1;
			}
		}
	}
	
	//Free the temporary Roman numeral string.
	free(ntemp);

	//Store the final converted decimal number.  
	*decimal = decimal_temp;

	return 0;
}

/* Add two Roman numerals.  See header file for full description. */
int roman_addition(const char * numeral_a, const char * numeral_b, char * numeral_sum) {

	//Check for null strings
	if(numeral_a == NULL || numeral_b == NULL || numeral_sum == NULL) {
		//Addition failed.
		return 1;
	}
	
	//Integers used for conversion and addition.  
	int decimal_a;
	int decimal_b;
	int decimal_sum;
	
	//Convert the operands to decimal, checking for flags from 
	//conversion functions.  
	if(convert_roman_to_decimal(numeral_a, &decimal_a) || convert_roman_to_decimal(numeral_b, &decimal_b)) {
	
		//Addition failed.
		return 1;
	}
	
	//Add the decimal values.
	decimal_sum = decimal_a + decimal_b;
	
	//Check if sum is within maximum value supported.  
	if(decimal_sum > MAX_DECIMAL) {
	
		//Addition failed.
		return 1;
	}
	
	//Convert decimal sum to Roman numeral sum, check for flag. 
	if(convert_decimal_to_roman(decimal_sum, numeral_sum)) {
	
		//Addition failed.
		return 1;
	}

	return 0;
}

/* Subtract two Roman numerals.  See header file for full description. */
int roman_subtraction(const char * numeral_a, const char * numeral_b, char * numeral_diff) {

	//Check for null string pointers.  
	if(numeral_a == NULL || numeral_b == NULL || numeral_diff == NULL) {
		//Subtraction failed.
		return 1;
	}
	
	//Integers used for conversion and subtraction.  
	int decimal_a;
	int decimal_b;
	int decimal_diff;
	
	//Convert the operands to decimal, checking for flags from 
	//conversion functions.  
	if(convert_roman_to_decimal(numeral_a, &decimal_a) || convert_roman_to_decimal(numeral_b, &decimal_b)) {
	
		//Subtraction failed.
		return 1;
	}
	
	//Subtract the decimal values.
	decimal_diff = decimal_a - decimal_b;
	
	//Check if difference is a valid decimal number.    
	if(decimal_diff < 1) {
	
		//Subtraction failed.
		return 1;
	}
	
	//Convert decimal difference to Roman numeral difference, check 
	//for flag. 
	if(convert_decimal_to_roman(decimal_diff, numeral_diff)) {
	
		//Subtraction failed.
		return 1;
	}

	return 0;
}

/* Allocates a C-style string to store Roman numerals.  See header 
file for more detailed description. */
char * allocate_roman_numeral_string() {

	//Allocate the string, set contents to zero, and return pointer. 
	char * temp_string = (char*)malloc(sizeof(char) + (strlen(MAX_LENGTH_ROMAN)+1));
	memset(temp_string, 0, (strlen(MAX_LENGTH_ROMAN)+1));

	return temp_string;
}

