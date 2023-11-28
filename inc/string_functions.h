/**
 * @file string_functions.h
 * @brief String functions header file
 * @author Markus Hehn
 * @date 28.11.2023
 * 
 * Functions for the processing of strings.
 */


#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H


#include <stdint.h>


uint32_t csv_to_integerarray(char *, int32_t *, uint32_t);
uint32_t csv_to_floatarray(char *, float *, uint32_t);
int32_t string_to_integer(char *);
float string_to_float(char *);
void integer_to_chararray(int32_t, char *, int32_t);
void float_to_chararray(float, char *, int32_t, uint32_t);


#endif
