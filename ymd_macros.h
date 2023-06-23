#define NO_MONTH    12
#define NO_DAY      7
#define LOW_BOUND_YEAR 1800
#define LEAP 100
#define NOT_LEAP 101

enum month {JAN=0, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

const char* str_month[] =   {"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                             "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

const int c_month[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5, 4}; // JAN - DEC, FEB_LeapYear

enum day {SUN=0, MON, TUE, WED, THU, FRI, SAT};

const char* str_day[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

///////////////////////////////////////////////////////////////////////////
//                      Tomohiko Sakamoto's Algorithm                    //
//                                                                       //
// day = (year+ (year/4)- (year/100)+ (year/400)+ t[month-1]+ day)% 7    //
//                                                                       //
//      Month Const                                                      //
// t[]=                                                                  //
// January: 0                                                            //
// February: 3 (in a regular year) or 4 (in a leap year)                 //
// March: 3                                                              //
// April: 6                                                              //
// May: 1                                                                //
// June: 4                                                               //
// July: 6                                                               //
// August: 2                                                             //
// September: 5                                                          //
// October: 0                                                            //
// November: 3                                                           //
// December: 5                                                           //
//                                                                       //
// After 1, March, 1800                                                  //
///////////////////////////////////////////////////////////////////////////