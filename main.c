#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "ymd_macros.h"

int power(int base, unsigned int p);
int str_num(const char* num_str);
int isLeapYear(const int year);
void print_date(const int year, const int month, const int date);
void print_month(const int year, const int month);
void print_year(const int year);

int main(const int argc, const char* argv[])
{
    int year,month,day,date,l_year;


    return 0;
}

int power(int base, unsigned int p)
{
    int temp = base;
    if(p == 0)
        return 1;
    for(int i=1; i<p; i++)
    {
        temp *= base;
    }
    return temp;
}

int str_num(const char* num_str)
{   int num_dig=0,num=0,i=0;
    while(num_str[i] != ' ' && num_str[i] != '\t' && num_str[i] != '\0')
    {   i++;
    }
    num_dig=i;
    for(i=0;i<num_dig;i++)
    {   if(num_str[i]<48 || num_str[i]>57)
            return -1;
        num += (int)((num_str[i]-48) * power(10,num_dig-i-1));
    }
    return num;
}

int isLeapYear(const int year)
{
    return  (year%400 == 0) ? LEAP :
            (year%100 == 0) ? NOT_LEAP :
            (year%4   == 0) ? LEAP : NOT_LEAP;
}