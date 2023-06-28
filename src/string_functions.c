/**
 * @file string_functions.c
 * @brief String functions source file
 * @author Markus Hehn
 * @date 06.04.2023
 */


#include <stdint.h>
#include "string_functions.h"


/**
 * @brief Function copies the values of a CSV-string (CSV = Comma Separated Values) into an integer-array and returns the number of values.
 * @param string:               CSV-string
 * @param integerarray:         Integer-array
 * @param array_length:         Size of the integer-array (avoids array overflow)
 * @return number of values
 */
uint32_t csv_to_integerarray(char *string, int32_t *integerarray, uint32_t array_length)
{
    uint32_t string_index = 0;
    uint32_t string_value_length = 0;
    uint32_t integerarray_index = 0;
    
    char *string_value_pointer;
    
    while((string[string_index] != '\r') && (string[string_index] != '\n') && (string[string_index] != '\0'))
    {
        if(string[string_index] == ',')
        {
            string_value_pointer = &string[string_index - string_value_length];
            
            if(integerarray_index < array_length)
                integerarray[integerarray_index++] = string_to_integer(string_value_pointer);
            
            string_value_length = 0;
        }
        else
        {
            string_value_length++;
        }
        
        string_index++;
    }
    
    string_value_pointer = &string[string_index - string_value_length];
    
    if(integerarray_index < array_length)
        integerarray[integerarray_index++] = string_to_integer(string_value_pointer);
    
    return integerarray_index;
}


/**
 * @brief Function copies the values of a CSV-string (CSV = Comma Separated Values) into a float-array and returns the number of values.
 * @param string:               CSV-string
 * @param floatarray:           Float-array
 * @param array_length:         Size of the float-array (avoids array overflow)
 * @return number of values
 */
uint32_t csv_to_floatarray(char *string, float *floatarray, uint32_t array_length)
{
    uint32_t string_index = 0;
    uint32_t string_value_length = 0;
    uint32_t floatarray_index = 0;
    
    char *string_value_pointer;
    
    while((string[string_index] != '\r') && (string[string_index] != '\n') && (string[string_index] != '\0'))
    {
        if(string[string_index] == ',')
        {
            string_value_pointer = &string[string_index - string_value_length];
            
            if(floatarray_index < array_length)
                floatarray[floatarray_index++] = string_to_float(string_value_pointer);
            
            string_value_length = 0;
        }
        else
        {
            string_value_length++;
        }
        
        string_index++;
    }
    
    string_value_pointer = &string[string_index - string_value_length];
    
    if(floatarray_index < array_length)
        floatarray[floatarray_index++] = string_to_float(string_value_pointer);
    
    return floatarray_index;
}


/**
 * @brief Function converts a string into an integer number. All characters up to the first '\r', '\n' or '\0' are considered.
 * @param string:               String to convert
 * @return number
 */
int32_t string_to_integer(char *string)
{
    uint8_t negative_flag = 0;
    uint32_t string_index = 0;
    int32_t number = 0;
    
    if(string[0] == '-')
    {
        negative_flag = 1;
        string_index = 1;
    }
    
    while((string[string_index] != '\r') && (string[string_index] != '\n') && (string[string_index] != '\0') && (string[string_index] != ','))
    {
        number *= 10;
        number += string[string_index] - '0';
        string_index++;
    }
    
    if(negative_flag)
        number = -number;
    
    return number;
}


/**
 * @brief Function converts a string into a float number. All characters up to the first '\r', '\n' or '\0' are considered.
 * @param string:               String to convert
 * @return number
 */
float string_to_float(char *string)
{
    uint8_t negative_flag = 0;
    uint8_t fractional_flag = 0;
    uint32_t string_index = 0;
    int32_t fractional_divisor = 1;
    float number = 0.0f;
    
    if(string[0] == '-')
    {
        negative_flag = 1;
        string_index = 1;
    }
    
    while((string[string_index] != '\r') && (string[string_index] != '\n') && (string[string_index] != '\0') && (string[string_index] != ','))
    {
        if(string[string_index] == '.')
        {
            fractional_flag = 1;
        }
        else
        {
            number *= 10.0f;
            number += string[string_index] - '0';
            
            if(fractional_flag == 1)
                fractional_divisor *= 10;
        }
        string_index++;
    }
    
    number /= fractional_divisor;
    
    if(negative_flag)
        number = -number;
    
    return number;
}


/**
 * @brief Function converts an integer number into a char-array (without '\0' at the end!).
 * @param number:               Number to convert (can be negative).
 * @param chararray:            Result will be copied here.
 * @param length:               Number of characters in the output. The number in the output is right aligned. If the number is negative, one additional digit is inserted for the sign.
 */
void integer_to_chararray(int32_t number, char *chararray, int32_t length)
{
    uint8_t minus_flag = 0;
    
    if(length < 0)                                                                                      // if the length is negative, the sign should also be printed
    {
        length = -length + 1;                                                                           // length with sign is one longer
    
        if(number < 0)
            minus_flag = 1;
    }
    
    if(number < 0)                                                                                      // if the number is negative, calculate the absolute value
        number = -number;
    
    for(int32_t i = length - 1 ; i >= 0 ; i--)                                                          // writes the least significant digit into the last position
    {
        if(number > 0)
        {
            chararray[i] = '0' + number % 10;
            number /= 10;
        }
        else
        {
            if(i == length - 1)                                                                         // in that case the input number can only be zero and no sign should be printed
                chararray[i] = '0';
            else
            {
                if(minus_flag == 1)
                {
                    chararray[i] = '-';                                                                 // print minus sign
                    minus_flag = 0;
                }
                else
                    chararray[i] = ' ';                                                                 // if nothing is to be printed, print spaces
            }
        }
    }
}


/**
 * @brief Function converts a float number into a char-array (without '\0' at the end!). Resulting length: 1 (sign) + abs(integer_length) + 1 (decimal point) + fractional_length
 * @param number:               Number to convert (can be negative).
 * @param chararray:            Result will be copied here.
 * @param integer_length:       Number of digits for the integer part in the output. The number in the output is right aligned. If the number is negative, one digit is inserted for the sign.
 * @param fractional_length:    Number of digits for the fractional part in the output.
 */
void float_to_chararray(float float_number, char *chararray, int32_t integer_length, uint32_t fractional_length)
{
    uint8_t minus_flag = 0;
    int32_t number = 0;
    int32_t length = 0;
    uint32_t fractional_factor = 1;
    
    for(uint32_t i = 0; i < fractional_length; i++)
    {
        fractional_factor *= 10;
    }
    
    number = float_number * fractional_factor;
    
    if(integer_length < 0)                                                                              // if the length is negative, the sign should also be printed
    {
        length = 1 - integer_length + 1 + fractional_length;                                            // length with sign is one longer
        
        if(number < 0)
            minus_flag = 1;
    }
    else
    {
        length = integer_length + 1 + fractional_length;
    }
    
    if(number < 0)                                                                                      // if the number is negative, calculate the absolute value
        number = -number;
    
    for(int32_t i = length - 1 ; i >= 0 ; i--)                                                          // writes the least significant digit into the last position
    {
        if(i == length - fractional_length - 1)                                                         // print the decimal point
        {
            chararray[i] = '.';
        }
        else
        {
            if(number > 0)                                                                              // print digit
            {
                chararray[i] = '0' + number % 10;
                number /= 10;
            }
            else
            {
                if((minus_flag == 1) && (i < length - fractional_length - 2))                           // if minus sign is to be printed, then only before decimal point
                {
                    chararray[i] = '-';                                                                 // print minus sign
                    minus_flag = 0;
                }
                else
                    if((i == length - fractional_length - 2) || (i > length - fractional_length - 1))   // print zero, if the integer part equals zero (leading zero) or after the decimal point up to the first digit
                        chararray[i] = '0';
                    else
                        chararray[i] = ' ';                                                             // if nothing is to be printed, print spaces
            }
        }
    }
}


