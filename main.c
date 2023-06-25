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
void check_h_v(const char* str);
int calc_day(const int year, const int month, const int date);
void print_date(const int year, const int month, const int date);
void print_month(const int year, const int month);
void print_year(const int year);
void print_help(void);

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
        {
            check_h_v(argv[1]);
            break;
        }
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

void check_h_v(const char* str)
{
    if((!strcmp(str,"-h")) || (!strcmp(str,"--help")))
        {
            print_help();
            exit(0);
        }
        if((!strcmp(str,"-v")) || (!strcmp(str,"--version")))
        {
            system("echo \x1B[92m");
            printf("Calendar Application\nVersion 1.0 (2023)\nFree Software by Thomas.");
            system("echo \x1B[0m");
            exit(0);
        }
}

int calc_day(const int year, const int month, const int date)
{
    int year_cal = (month<2) ? year-1 : year; 
    int day = (year_cal +(year_cal/4) -(year_cal/100) +(year_cal/400) +month_const[month] +date) % 7;
    return day;
}

void print_date(const int year, const int month, const int date)
{
    int day = calc_day(year, month, date);
    system("echo \x1B[92m");
    printf("%4s%4s%6s\n","DD","MM","YYYY");
    printf("%4d%4d%6d  (%s)",date,month+1,year,day_const_str[day]);
    if(isLeapYear(year))
        printf("  (Leap year)");
    system("echo \x1B[0m");
}

void print_month(const int year, const int month)
{
    int space;
    int first_day = calc_day(year, month, 1);
    int leap_year = isLeapYear(year);
    system("echo \x1B[92m");
    printf("%20s%15d\n\n",month_const_str[month],year);
    for(int i=0; i<NO_DAY; i++)
    {
        printf("%5s",day_const_str[i]);
    }
    printf("\n");
    for(space=0; space<first_day; space++)
    {
        printf("     "); // 5 * space 
    }
    for(int day_count=1; day_count<=month_limit[month]; day_count++)
    {
        printf("%5d",day_count);
        if(((space+day_count)%7 == 0) && (day_count!=month_limit[month]))
            printf("\n");
    }
    if(leap_year && month==FEB)
        printf("%5d", 29);
    system("echo \x1B[0m");
}

void print_year(const int year)
{
    printf("Later\n");
}

void print_help(void)
{
    system("echo \x1B[92m");
    printf("Usage :\x1B[93m");
    printf("\tCalendar {Year}                : print out the calendar for that year\n");
    printf("\t\t {Year} {Month}        : print out the month for that year\n");
    printf("\t\t {Year} {Month} {Date} : print out the day of the week for that date\n");
    system("echo \x1B[94m   +------------------------------------------------+\x1B[93m");
    printf("\n{Month}\n");
    printf("\t\"JAN\" |  1\n\t\"FEB\" |  2\n\t\"MAR\" |  3\n\t\"APR\" |  4\n");
    printf("\t\"MAY\" |  5\n\t\"JUN\" |  6\n\t\"JUL\" |  7\n\t\"AUG\" |  8\n");
    printf("\t\"SEP\" |  9\n\t\"OCT\" | 10\n\t\"NOV\" | 11\n\t\"DEC\" | 12\n");
    system("echo \x1B[94m   +------------------------------------------------+\x1B[0m");   
}