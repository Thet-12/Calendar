// Calendar CLI App
// Author : Thet
// 24.6.2023

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "ymd_macros.h"

int power(int base, unsigned int p);
int str_num(const char* num_str);
int isLeapYear(const int year);
int year_num(const char* year_str);
int month_num(const char* month_str);
int date_num(const int month, const char* date_str);
void print_date(const int year, const int month, const int date);
void print_month(const int year, const int month);
void print_year(const int year);

int main(const int argc, const char* argv[])
{
    int year, month, date;

    switch (argc)
    {
    case 1:
        system("echo \x1B[91mInsufficient Arguments\x1B[0m\n");
        return 0;
    case 2:
        year = year_num(argv[1]);
        if(year == ERR)
            break;
        print_year(year);
        return 0;
    case 3:
        year = year_num(argv[1]);
        month = month_num(argv[2]);
        if(year == ERR || month == ERR)
            break;
        print_month(year, month);
        return 0;
    case 4:
        year = year_num(argv[1]);
        month = month_num(argv[2]);
        date = date_num(month, argv[3]);
        if(year == ERR || month == ERR || date == ERR)
            break;
        print_date(year, month, date);
        return 0;
    default:
        break;
    }
    system("echo \x1B[91mWrong Arguments\x1B[0m\n");
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
            return ERR;
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

int year_num(const char* year_str)
{
    int year = str_num(year_str);
    year = (year < 1800 || year > 3000) ? ERR : year;
    return  year;
}

int month_num(const char* month_str)
{
    int month = str_num(month_str);
    if(month != ERR)
        return (month>12) ? ERR : month - 1;

    for(int i=0; i<NO_MONTH; i++)
    {
        if(!strcmp(month_const_str[i],month_str))
            month = i;
    }
    return month;
}

int date_num(const int month, const char* date_str)
{
    int date = str_num(date_str);
    if(date < 1 || date > 31)
        date = ERR;
    else if(month == FEB && date > 29)
        date = ERR;
    else if(month == APR || month == JUN || month == SEP || month == NOV)
    {
        if(date > 30)
            date = ERR;
    }
    return  date;
}

void print_date(const int year, const int month, const int date)
{
    int leap_flag = isLeapYear(year);
    int year_cal = (month<2) ? year-1 : year; 
    int day = (year_cal +(year_cal/4) -(year_cal/100) +(year_cal/400) +month_const[month] +date) % 7;
    system("echo \x1B[92m");
    printf("DD\tMM\tYYYY\n");
    printf("%2d\t%2d\t%4d\t(%s)",date,month+1,year,day_const_str[day]);
    if(leap_flag == LEAP)
        printf("\t(Leap year)");
    system("echo \x1B[0m");
}

void print_month(const int year, const int month)
{
    printf("Later\n");
}

void print_year(const int year)
{
    printf("Later\n");
}