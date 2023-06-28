#include <stdio.h>
#include <stdint.h>
#include "string_functions.h"


int main(void)
{
    printf("\nstring to number functions test\n");
    
    char test_int_string[100] = {'-','1','2','3','4','\0'};
    char test_float_string_1[100] = {'-','1','2','3','4','.','5','6','7','8','9','\0'};
    char test_float_string_2[100] = {'-','1','\0'};
    
    int32_t int_number = string_to_integer(test_int_string);
    float float_number_1 = string_to_float(test_float_string_1);
    float float_number_2 = string_to_float(test_float_string_2);
    
    printf("int number is: %d\n",int_number);
    printf("float number 1 is: %f\n",float_number_1);
    printf("float number 2 is: %f\n",float_number_2);
    
    
    
    printf("\ncsv to array functions test\n");
    
    char test_int_csv_string[100] = {'-','1','2','3','4',',','0','1','2','3','4',',',',',',',',',',','\0'};
    int32_t integerarray[10];
    uint32_t int_csv_number = csv_to_integerarray(test_int_csv_string, integerarray, 3);
    
    printf("number: %d; CSV-Values: ",int_csv_number);
    
    for(uint32_t i = 0; i < int_csv_number; i++)
    {
        printf("%d ,",integerarray[i]);
    }
    printf("\n");
    
    char test_float_csv_string[100] = "-1234.2,-0.2342,-1245.000,10,,\n";
    float floatarray[10];
    uint32_t float_csv_number = csv_to_floatarray(test_float_csv_string, floatarray, 10);
    
    printf("number: %d; CSV-Values: ",float_csv_number);
    
    for(uint32_t i = 0; i < float_csv_number; i++)
    {
        printf("%f,",floatarray[i]);
    }
    printf("\n");
    
    
    
    printf("\nnumber to chararray functions test\n");
    
    char chararray[7];
    float float_number = -0.02;
    int32_t integer_length = -1;
    uint32_t fractional_length = 2;
    
    float_to_chararray(float_number, chararray, integer_length, fractional_length);
    
    chararray[6] = '\0';
    
    
    
    printf("chararray=%s\n",chararray);
    
    
    char data_string[20];
    
    integer_to_chararray(100, data_string, 8);
            
    data_string[8] = '\r';
    data_string[9] = '\n';
    data_string[10] = '\0';
    
    printf("data_string: %s\n",data_string);
    
    for(uint32_t i = 0; i < 20; i++)
        printf("%d,",(uint8_t)data_string[i]);
    
}
