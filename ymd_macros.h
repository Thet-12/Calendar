#define NO_MONTH    12
#define NO_DAY      7
#define LOW_BOUND_YEAR 1800
#define LEAP 1
#define NOT_LEAP 0
#define ERR -1

enum month_num {JAN=0, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

const char* month_const_str[] =   {"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                             "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

const int month_const[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; // JAN - DEC, FEB_LeapYear
const int month_limit[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

enum day_num {SUN=0, MON, TUE, WED, THU, FRI, SAT};

const char* day_const_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

///////////////////////////////////////////////////////////////////////////
//                      Tomohiko Sakamoto's Algorithm                    //
//                                                                       //
// day = (year+ (year/4)- (year/100)+ (year/400)+ t[month-1]+ day)% 7    //
// if(Jan && FEB) year-1                                                 //
//                                                                       //
// t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}                            //
// January: 0                                            (31)            //
// February: 3                                           (28, 29) *      //
// March: 2                                              (31)            //
// April: 5                                              (30)     *      //
// May: 0                                                (31)            //
// June: 3                                               (30)     *      //
// July: 5                                               (31)            //
// August: 1                                             (31)            //
// September: 4                                          (30)     *      //
// October: 6                                            (31)            //
// November: 2                                           (30)     *      //
// December: 4                                           (31)            //
//                                                                       //
// After 1, March, 1800                                                  //
///////////////////////////////////////////////////////////////////////////