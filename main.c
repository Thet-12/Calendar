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
char* num_str(const int num, char* str, const int size);
int isLeapYear(const int year);
int year_num(const char* year_str);
int month_num(const char* month_str);
int date_num(const int month, const char* date_str);
void check_h_v(const char* str);
int calc_day(const int year, const int month, const int date);
int calc_month(const int year, const int month);
void print_date(const int year, const int month, const int date);
void print_month(const int year, const int month);
void print_year(const int year);
void print_help(void);

char year_calendar [12][56][5]; // [month] [week (7*8)] [day_print_length]

int main(const int argc, const char* argv[])
{
    int year, month, date;
    
    memset(year_calendar,'\0',12*56*5);
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

char* num_str(const int num, char* str, const int size)
{
    int num_length = 1, tenth = 10, i, j=0;
    while(num/tenth > 0)
    {
        num_length++;
        tenth *= 10;
    }
    if(num_length >= size)
    {
        str[0] = '\0';
        return '\0';
    }
    for(i=0,j=power(10,num_length-j-1); i<num_length; i++,j/=10)
    {
        str[i] = ((num/j)%10) + 48;
    }
    str[i] = '\0';
    return str;
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

int calc_month(const int year, const int month)
{
    char year_str[5], date_str[5];
    int space = 0;
    int first_day = calc_day(year, month, 1);
    num_str(year, year_str, 5);
    strncpy(year_calendar[month][3], month_const_str[month], 5);
    strncpy(year_calendar[month][6], year_str, 5);
    for(int i=0; i<NO_DAY; i++)
    {
        strncpy(year_calendar[month][7+i], day_const_str[i], 5);
    }
    for(space=0; space<first_day; space++)
    {
        strncpy(year_calendar[month][14+space], " ", 5);
    }
    for(int day_count=1; day_count<=month_limit[month]; day_count++)
    {
        num_str(day_count,date_str,5);
        strncpy(year_calendar[month][13+space+day_count], date_str, 5);
    }
    if(isLeapYear(year) && month==FEB)
    {
        num_str(29,date_str,5);
        strncpy(year_calendar[month][13+space+29], date_str, 5);
    }
    return 0;
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
    calc_month(year,month);
    system("echo \x1B[92m");
    for(int j=0; j<56; j++)
    {
        printf("%5s",year_calendar[month][j]);
        if(j!=0 && j%7==6)
            printf("\n");
    }
    system("echo \x1B[0m");
}

void print_year(const int year)
{
    char year_str[5];
    num_str(year,year_str,5);
    int i,j,k;
    for(int i=0; i<NO_MONTH; i++)
    {
        calc_month(year,i);
    }
    system("echo \x1B[92m");
    printf("%60s\n\n",year_str);
    for(int line=0,i=0; line<32; line++,i++)
    {   
        if(i>7)
        {
            i = 0;
            printf("\n");
        }
        for(j=0; j<3; j++)
        {
            for(k=0; k<7; k++)
            {
                printf("%5s",year_calendar[((line/8)*3)+j][(i*7)+k]);
            }
            printf("%5s"," ");
        }
        printf("\n");
    }
    system("echo \x1B[0m");
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