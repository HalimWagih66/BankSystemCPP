//ProgrammingAdivces.com
//Mohammed Abu-Hadhoud
#pragma warning(disable : 4996)
#include "../headers/date_utils.h"
#include<iostream>
#include<string>
#include "../headers/string_utils.h"

using namespace std;

// Default constructor: initializes to current system date
DateUtils::DateUtils()
{
    time_t t = time(0);
    tm* now = localtime(&t);
    _Day = now->tm_mday;
    _Month = now->tm_mon + 1;
    _Year = now->tm_year + 1900;
}

// Construct from string "dd/mm/yyyy"
DateUtils::DateUtils(string sDate)
{
    vector <string> vDate;
    vDate = StringUtils::SplitString(sDate, "/");

    _Day = stoi(vDate[0]);
    _Month = stoi(vDate[1]);
    _Year = stoi(vDate[2]);
}

// Construct from day, month, year
DateUtils::DateUtils(short Day, short Month, short Year)
{
    _Day = Day;
    _Month = Month;
    _Year = Year;
}

// Construct from day order in year and year
DateUtils::DateUtils(short DateOrderInYear, short Year)
{
    DateUtils Date1 = DateUtils::GetDateFromDayOrderInYear(DateOrderInYear, Year);
    _Day = Date1.Day;
    _Month = Date1.Month;
    _Year = Date1.Year;
}

// Setters and getters for day, month, year
void DateUtils::SetDay(short Day) {
    _Day = Day;
}

short DateUtils::GetDay() {
    return _Day;
}

void DateUtils::SetMonth(short Month) {
    _Month = Month;
}

short DateUtils::GetMonth() {
    return _Month;
}

void DateUtils::SetYear(short Year) {
    _Year = Year;
}

short DateUtils::GetYear() {
    return _Year;
}

// Print date in "dd/mm/yyyy" format
void DateUtils::Print()
{
    cout << DateToString() << endl;
}

// Get current system date as DateUtils object
DateUtils DateUtils::GetSystemDate()
{
    time_t t = time(0);
    tm* now = localtime(&t);

    short Day, Month, Year;

    Year = now->tm_year + 1900;
    Month = now->tm_mon + 1;
    Day = now->tm_mday;

    return DateUtils(Day, Month, Year);
}

// Get current system date and time as string
string DateUtils::GetSystemDateTimeString()
{
    time_t t = time(0);
    tm* now = localtime(&t);

    short Day, Month, Year, Hour, Minute, Second;

    Year = now->tm_year + 1900;
    Month = now->tm_mon + 1;
    Day = now->tm_mday;
    Hour = now->tm_hour;
    Minute = now->tm_min;
    Second = now->tm_sec;

    return (to_string(Day) + "/" + to_string(Month) + "/"
        + to_string(Year) + " - "
        + to_string(Hour) + ":" + to_string(Minute)
        + ":" + to_string(Second));
}

// Static: checks if a date is valid
bool DateUtils::IsValidDate(DateUtils Date)
{
    if (Date.Day < 1 || Date.Day>31)
        return false;

    if (Date.Month < 1 || Date.Month>12)
        return false;

    if (Date.Month == 2)
    {
        if (isLeapYear(Date.Year))
        {
            if (Date.Day > 29)
                return false;
        }
        else
        {
            if (Date.Day > 28)
                return false;
        }
    }

    short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

    if (Date.Day > DaysInMonth)
        return false;

    return true;
}

// Checks if the current date object is valid
bool DateUtils::IsValid()
{
    return IsValidDate(*this);
}

// Static: converts a date to string
string DateUtils::DateToString(DateUtils Date)
{
    return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}

// Converts current date object to string
string DateUtils::DateToString()
{
    return  DateToString(*this);
}

// Static: checks if a year is leap year
bool DateUtils::isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

// Checks if the object's year is leap year
bool DateUtils::isLeapYear()
{
    return isLeapYear(_Year);
}

// Static: returns number of days in a year
short DateUtils::NumberOfDaysInAYear(short Year)
{
    return  isLeapYear(Year) ? 366 : 365;
}

// Returns number of days in object's year
short DateUtils::NumberOfDaysInAYear()
{
    return  NumberOfDaysInAYear(_Year);
}

// Static: returns number of hours in a year
short DateUtils::NumberOfHoursInAYear(short Year)
{
    return  NumberOfDaysInAYear(Year) * 24;
}

// Returns number of hours in object's year
short DateUtils::NumberOfHoursInAYear()
{
    return  NumberOfHoursInAYear(_Year);
}

// Static: returns number of minutes in a year
int DateUtils::NumberOfMinutesInAYear(short Year)
{
    return  NumberOfHoursInAYear(Year) * 60;
}

// Returns number of minutes in object's year
int DateUtils::NumberOfMinutesInAYear()
{
    return  NumberOfMinutesInAYear(_Year);
}

// Static: returns number of seconds in a year
int DateUtils::NumberOfSecondsInAYear(short Year)
{
    return  NumberOfMinutesInAYear(Year) * 60;
}

// Returns number of seconds in object's year
int DateUtils::NumberOfSecondsInAYear()
{
    return  NumberOfSecondsInAYear(_Year);
}

// Static: returns number of days in a month for a given year
short DateUtils::NumberOfDaysInAMonth(short Month, short Year)
{
    if (Month < 1 || Month>12)
        return  0;

    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
}

// Returns number of days in object's month/year
short DateUtils::NumberOfDaysInAMonth()
{
    return NumberOfDaysInAMonth(_Month, _Year);
}

// Static: returns number of hours in a month
short DateUtils::NumberOfHoursInAMonth(short Month, short Year)
{
    return  NumberOfDaysInAMonth(Month, Year) * 24;
}

// Returns number of hours in object's month/year
short DateUtils::NumberOfHoursInAMonth()
{
    return  NumberOfDaysInAMonth(_Month, _Year) * 24;
}

// Static: returns number of minutes in a month
int DateUtils::NumberOfMinutesInAMonth(short Month, short Year)
{
    return  NumberOfHoursInAMonth(Month, Year) * 60;
}

// Returns number of minutes in object's month/year
int DateUtils::NumberOfMinutesInAMonth()
{
    return  NumberOfHoursInAMonth(_Month, _Year) * 60;
}

// Static: returns number of seconds in a month
int DateUtils::NumberOfSecondsInAMonth(short Month, short Year)
{
    return  NumberOfMinutesInAMonth(Month, Year) * 60;
}

// Returns number of seconds in object's month/year
int DateUtils::NumberOfSecondsInAMonth()
{
    return  NumberOfMinutesInAMonth(_Month, _Year) * 60;
}

// Static: calculates day of week (0=Sun, 6=Sat) for given date
short DateUtils::DayOfWeekOrder(short Day, short Month, short Year)
{
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

// Returns day of week for object's date
short DateUtils::DayOfWeekOrder()
{
    return DayOfWeekOrder(_Day, _Month, _Year);
}

// Static: returns short name for day of week
string DateUtils::DayShortName(short DayOfWeekOrder)
{
    string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    return arrDayNames[DayOfWeekOrder];
}

// Static: returns short name for day of week for given date
string DateUtils::DayShortName(short Day, short Month, short Year)
{
    string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
}

// Returns short name for day of week for object's date
string DateUtils::DayShortName()
{
    string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
}

// Static: returns short name for month
string DateUtils::MonthShortName(short MonthNumber)
{
    string Months[12] = { "Jan", "Feb", "Mar",
                       "Apr", "May", "Jun",
                       "Jul", "Aug", "Sep",
                       "Oct", "Nov", "Dec"
    };
    return (Months[MonthNumber - 1]);
}

// Returns short name for object's month
string DateUtils::MonthShortName()
{
    return MonthShortName(_Month);
}

// Static: prints calendar for a given month/year
void DateUtils::PrintMonthCalendar(short Month, short Year)
{
    int NumberOfDays;
    int current = DayOfWeekOrder(1, Month, Year);
    NumberOfDays = NumberOfDaysInAMonth(Month, Year);

    printf("\n  _______________%s_______________\n\n",
        MonthShortName(Month).c_str());
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    int i;
    for (i = 0; i < current; i++)
        printf("     ");

    for (int j = 1; j <= NumberOfDays; j++)
    {
        printf("%5d", j);
        if (++i == 7)
        {
            i = 0;
            printf("\n");
        }
    }
    printf("\n  _________________________________\n");
}

// Prints calendar for object's month/year
void DateUtils::PrintMonthCalendar()
{
    PrintMonthCalendar(_Month, _Year);
}

// Static: prints calendar for a given year
void DateUtils::PrintYearCalendar(int Year)
{
    printf("\n  _________________________________\n\n");
    printf("           Calendar - %d\n", Year);
    printf("  _________________________________\n");

    for (int i = 1; i <= 12; i++)
    {
        PrintMonthCalendar(i, Year);
    }
}

// Prints calendar for object's year
void DateUtils::PrintYearCalendar()
{
    printf("\n  _________________________________\n\n");
    printf("           Calendar - %d\n", _Year);
    printf("  _________________________________\n");

    for (int i = 1; i <= 12; i++)
    {
        PrintMonthCalendar(i, _Year);
    }
}

// Static: returns number of days from start of year to given date
short DateUtils::DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
{
    short TotalDays = 0;
    for (int i = 1; i <= Month - 1; i++)
    {
        TotalDays += NumberOfDaysInAMonth(i, Year);
    }
    TotalDays += Day;
    return TotalDays;
}

// Returns number of days from start of year to object's date
short DateUtils::DaysFromTheBeginingOfTheYear()
{
    short TotalDays = 0;
    for (int i = 1; i <= _Month - 1; i++)
    {
        TotalDays += NumberOfDaysInAMonth(i, _Year);
    }
    TotalDays += _Day;
    return TotalDays;
}

// Static: gets date from day order in year
DateUtils DateUtils::GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
{
    DateUtils Date;
    short RemainingDays = DateOrderInYear;
    short MonthDays = 0;

    Date.Year = Year;
    Date.Month = 1;

    while (true)
    {
        MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

        if (RemainingDays > MonthDays)
        {
            RemainingDays -= MonthDays;
            Date.Month++;
        }
        else
        {
            Date.Day = RemainingDays;
            break;
        }
    }
    return Date;
}

// Adds days to current date object
void DateUtils::AddDays(short Days)
{
    short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
    short MonthDays = 0;
    _Month = 1;

    while (true)
    {
        MonthDays = NumberOfDaysInAMonth(_Month, _Year);

        if (RemainingDays > MonthDays)
        {
            RemainingDays -= MonthDays;
            _Month++;

            if (_Month > 12)
            {
                _Month = 1;
                _Year++;
            }
        }
        else
        {
            _Day = RemainingDays;
            break;
        }
    }
}

// Static: adds one day to given date
DateUtils DateUtils::AddOneDay(DateUtils Date)
{
    if (IsLastDayInMonth(Date))
    {
        if (IsLastMonthInYear(Date.Month))
        {
            Date.Month = 1;
            Date.Day = 1;
            Date.Year++;
        }
        else
        {
            Date.Day = 1;
            Date.Month++;
        }
    }
    else
    {
        Date.Day++;
    }
    return Date;
}

// Adds one day to current date object
void DateUtils::AddOneDay()
{
    *this = AddOneDay(*this);
}

// Swaps two DateUtils objects
void DateUtils::SwapDates(DateUtils& Date1, DateUtils& Date2)
{
    DateUtils TempDate;
    TempDate = Date1;
    Date1 = Date2;
    Date2 = TempDate;
}

// Static: checks if Date1 is before Date2
bool DateUtils::IsDate1BeforeDate2(DateUtils Date1, DateUtils Date2)
{
    return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}

// Checks if current date is before Date2
bool DateUtils::IsDateBeforeDate2(DateUtils Date2)
{
    return  IsDate1BeforeDate2(*this, Date2);
}

// Static: checks if Date1 equals Date2
bool DateUtils::IsDate1EqualDate2(DateUtils Date1, DateUtils Date2)
{
    return  (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
}

// Checks if current date equals Date2
bool DateUtils::IsDateEqualDate2(DateUtils Date2)
{
    return  IsDate1EqualDate2(*this, Date2);
}

// Static: checks if date is last day in month
bool DateUtils::IsLastDayInMonth(DateUtils Date)
{
    return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
}

// Checks if current date is last day in month
bool DateUtils::IsLastDayInMonth()
{
    return IsLastDayInMonth(*this);
}

// Static: checks if month is last month in year
bool DateUtils::IsLastMonthInYear(short Month)
{
    return (Month == 12);
}

// Static: increases date by one week
DateUtils DateUtils::IncreaseDateByOneWeek(DateUtils& Date)
{
    for (int i = 1; i <= 7; i++)
    {
        Date = AddOneDay(Date);
    }
    return Date;
}

// Increases current date by one week
void DateUtils::IncreaseDateByOneWeek()
{
    IncreaseDateByOneWeek(*this);
}

// Increases date by X weeks
DateUtils DateUtils::IncreaseDateByXWeeks(short Weeks, DateUtils& Date)
{
    for (short i = 1; i <= Weeks; i++)
    {
        Date = IncreaseDateByOneWeek(Date);
    }
    return Date;
}

// Increases current date by X weeks
void DateUtils::IncreaseDateByXWeeks(short Weeks)
{
    IncreaseDateByXWeeks(Weeks, *this);
}

// Static: increases date by one month
DateUtils DateUtils::IncreaseDateByOneMonth(DateUtils& Date)
{
    if (Date.Month == 12)
    {
        Date.Month = 1;
        Date.Year++;
    }
    else
    {
        Date.Month++;
    }
    short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
    if (Date.Day > NumberOfDaysInCurrentMonth)
    {
        Date.Day = NumberOfDaysInCurrentMonth;
    }
    return Date;
}

// Increases current date by one month
void DateUtils::IncreaseDateByOneMonth()
{
    IncreaseDateByOneMonth(*this);
}

// Static: increases date by X days
DateUtils DateUtils::IncreaseDateByXDays(short Days, DateUtils& Date)
{
    for (short i = 1; i <= Days; i++)
    {
        Date = AddOneDay(Date);
    }
    return Date;
}

// Increases current date by X days
void DateUtils::IncreaseDateByXDays(short Days)
{
    IncreaseDateByXDays(Days, *this);
}

// Static: increases date by X months
DateUtils DateUtils::IncreaseDateByXMonths(short Months, DateUtils& Date)
{
    for (short i = 1; i <= Months; i++)
    {
        Date = IncreaseDateByOneMonth(Date);
    }
    return Date;
}

// Increases current date by X months
void DateUtils::IncreaseDateByXMonths(short Months)
{
    IncreaseDateByXMonths(Months, *this);
}

// Static: increases date by one year
DateUtils DateUtils::IncreaseDateByOneYear(DateUtils& Date)
{
    Date.Year++;
    return Date;
}

// Increases current date by one year
void DateUtils::IncreaseDateByOneYear()
{
    IncreaseDateByOneYear(*this);
}

// Static: increases date by X years
DateUtils DateUtils::IncreaseDateByXYears(short Years, DateUtils& Date)
{
    Date.Year += Years;
    return Date;
}

// Increases current date by X years
void DateUtils::IncreaseDateByXYears(short Years)
{
    IncreaseDateByXYears(Years, *this);
}

// Static: increases date by one decade
DateUtils DateUtils::IncreaseDateByOneDecade(DateUtils& Date)
{
    Date.Year += 10;
    return Date;
}

// Increases current date by one decade
void DateUtils::IncreaseDateByOneDecade()
{
    IncreaseDateByOneDecade(*this);
}

// Static: increases date by X decades
DateUtils DateUtils::IncreaseDateByXDecades(short Decade, DateUtils& Date)
{
    Date.Year += Decade * 10;
    return Date;
}

// Increases current date by X decades
void DateUtils::IncreaseDateByXDecades(short Decade)
{
    IncreaseDateByXDecades(Decade, *this);
}

// Static: increases date by one century
DateUtils DateUtils::IncreaseDateByOneCentury(DateUtils& Date)
{
    Date.Year += 100;
    return Date;
}

// Increases current date by one century
void DateUtils::IncreaseDateByOneCentury()
{
    IncreaseDateByOneCentury(*this);
}

// Static: increases date by one millennium
DateUtils DateUtils::IncreaseDateByOneMillennium(DateUtils& Date)
{
    Date.Year += 1000;
    return Date;
}

// Increases current date by one millennium
DateUtils DateUtils::IncreaseDateByOneMillennium()
{
    return IncreaseDateByOneMillennium(*this);
}

// Static: decreases date by one day
DateUtils DateUtils::DecreaseDateByOneDay(DateUtils Date)
{
    if (Date.Day == 1)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Day = 31;
            Date.Year--;
        }
        else
        {
            Date.Month--;
            Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
        }
    }
    else
    {
        Date.Day--;
    }
    return Date;
}

// Decreases current date by one day
void DateUtils::DecreaseDateByOneDay()
{
    DecreaseDateByOneDay(*this);
}

// Static: decreases date by one week
DateUtils DateUtils::DecreaseDateByOneWeek(DateUtils& Date)
{
    for (int i = 1; i <= 7; i++)
    {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

// Decreases current date by one week
void DateUtils::DecreaseDateByOneWeek()
{
    DecreaseDateByOneWeek(*this);
}

// Static: decreases date by X weeks
DateUtils DateUtils::DecreaseDateByXWeeks(short Weeks, DateUtils& Date)
{
    for (short i = 1; i <= Weeks; i++)
    {
        Date = DecreaseDateByOneWeek(Date);
    }
    return Date;
}

// Decreases current date by X weeks
void DateUtils::DecreaseDateByXWeeks(short Weeks)
{
    DecreaseDateByXWeeks(Weeks, *this);
}

// Static: decreases date by one month
DateUtils DateUtils::DecreaseDateByOneMonth(DateUtils& Date)
{
    if (Date.Month == 1)
    {
        Date.Month = 12;
        Date.Year--;
    }
    else
        Date.Month--;

    short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
    if (Date.Day > NumberOfDaysInCurrentMonth)
    {
        Date.Day = NumberOfDaysInCurrentMonth;
    }
    return Date;
}

// Decreases current date by one month
void DateUtils::DecreaseDateByOneMonth()
{
    DecreaseDateByOneMonth(*this);
}

// Static: decreases date by X days
DateUtils DateUtils::DecreaseDateByXDays(short Days, DateUtils& Date)
{
    for (short i = 1; i <= Days; i++)
    {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

// Decreases current date by X days
void DateUtils::DecreaseDateByXDays(short Days)
{
    DecreaseDateByXDays(Days, *this);
}

// Static: decreases date by X months
DateUtils DateUtils::DecreaseDateByXMonths(short Months, DateUtils& Date)
{
    for (short i = 1; i <= Months; i++)
    {
        Date = DecreaseDateByOneMonth(Date);
    }
    return Date;
}

// Decreases current date by X months
void DateUtils::DecreaseDateByXMonths(short Months)
{
    DecreaseDateByXMonths(Months, *this);
}

// Static: decreases date by one year
DateUtils DateUtils::DecreaseDateByOneYear(DateUtils& Date)
{
    Date.Year--;
    return Date;
}

// Decreases current date by one year
void DateUtils::DecreaseDateByOneYear()
{
    DecreaseDateByOneYear(*this);
}

// Static: decreases date by X years
DateUtils DateUtils::DecreaseDateByXYears(short Years, DateUtils& Date)
{
    Date.Year -= Years;
    return Date;
}

// Decreases current date by X years
void DateUtils::DecreaseDateByXYears(short Years)
{
    DecreaseDateByXYears(Years, *this);
}

// Static: decreases date by one decade
DateUtils DateUtils::DecreaseDateByOneDecade(DateUtils& Date)
{
    Date.Year -= 10;
    return Date;
}

// Decreases current date by one decade
void DateUtils::DecreaseDateByOneDecade()
{
    DecreaseDateByOneDecade(*this);
}

// Static: decreases date by X decades
DateUtils DateUtils::DecreaseDateByXDecades(short Decades, DateUtils& Date)
{
    Date.Year -= Decades * 10;
    return Date;
}

// Decreases current date by X decades
void DateUtils::DecreaseDateByXDecades(short Decades)
{
    DecreaseDateByXDecades(Decades, *this);
}

// Static: decreases date by one century
DateUtils DateUtils::DecreaseDateByOneCentury(DateUtils& Date)
{
    Date.Year -= 100;
    return Date;
}

// Decreases current date by one century
void DateUtils::DecreaseDateByOneCentury()
{
    DecreaseDateByOneCentury(*this);
}

// Static: decreases date by one millennium
DateUtils DateUtils::DecreaseDateByOneMillennium(DateUtils& Date)
{
    Date.Year -= 1000;
    return Date;
}

// Decreases current date by one millennium
void DateUtils::DecreaseDateByOneMillennium()
{
    DecreaseDateByOneMillennium(*this);
}

// Static: checks if date is end of week (Saturday)
short DateUtils::IsEndOfWeek(DateUtils Date)
{
    return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
}

// Checks if current date is end of week
short DateUtils::IsEndOfWeek()
{
    return IsEndOfWeek(*this);
}

// Static: checks if date is weekend (Friday or Saturday)
bool DateUtils::IsWeekEnd(DateUtils Date)
{
    short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    return  (DayIndex == 5 || DayIndex == 6);
}

// Checks if current date is weekend
bool DateUtils::IsWeekEnd()
{
    return  IsWeekEnd(*this);
}

// Static: checks if date is business day (not weekend)
bool DateUtils::IsBusinessDay(DateUtils Date)
{
    return !IsWeekEnd(Date);
}

// Checks if current date is business day
bool DateUtils::IsBusinessDay()
{
    return  IsBusinessDay(*this);
}

// Static: returns days until end of week
short DateUtils::DaysUntilTheEndOfWeek(DateUtils Date)
{
    return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
}

// Returns days until end of week for current date
short DateUtils::DaysUntilTheEndOfWeek()
{
    return  DaysUntilTheEndOfWeek(*this);
}

// Static: returns days until end of month
short DateUtils::DaysUntilTheEndOfMonth(DateUtils Date1)
{
    DateUtils EndOfMontDate;
    EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
    EndOfMontDate.Month = Date1.Month;
    EndOfMontDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfMontDate, true);
}

// Returns days until end of month for current date
short DateUtils::DaysUntilTheEndOfMonth()
{
    return DaysUntilTheEndOfMonth(*this);
}

// Static: returns days until end of year
short DateUtils::DaysUntilTheEndOfYear(DateUtils Date1)
{
    DateUtils EndOfYearDate;
    EndOfYearDate.Day = 31;
    EndOfYearDate.Month = 12;
    EndOfYearDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfYearDate, true);
}

// Returns days until end of year for current date
short DateUtils::DaysUntilTheEndOfYear()
{
    return  DaysUntilTheEndOfYear(*this);
}

// Static: calculates business days between two dates
short DateUtils::CalculateBusinessDays(DateUtils DateFrom, DateUtils DateTo)
{
    short Days = 0;
    while (IsDate1BeforeDate2(DateFrom, DateTo))
    {
        if (IsBusinessDay(DateFrom))
            Days++;

        DateFrom = AddOneDay(DateFrom);
    }
    return Days;
}

// Static: calculates vacation days (same as business days)
short DateUtils::CalculateVacationDays(DateUtils DateFrom, DateUtils DateTo)
{
    return CalculateBusinessDays(DateFrom, DateTo);
}

// Static: calculates return date after vacation days, skipping weekends
DateUtils DateUtils::CalculateVacationReturnDate(DateUtils DateFrom, short VacationDays)
{
    short WeekEndCounter = 0;
    for (short i = 1; i <= VacationDays; i++)
    {
        if (IsWeekEnd(DateFrom))
            WeekEndCounter++;

        DateFrom = AddOneDay(DateFrom);
    }
    for (short i = 1; i <= WeekEndCounter; i++)
        DateFrom = AddOneDay(DateFrom);

    return DateFrom;
}

// Static: checks if Date1 is after Date2
bool DateUtils::IsDate1AfterDate2(DateUtils Date1, DateUtils Date2)
{
    return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
}

// Checks if current date is after Date2
bool DateUtils::IsDateAfterDate2(DateUtils Date2)
{
    return IsDate1AfterDate2(*this, Date2);
}

// Static: compares two dates (before, equal, after)
DateUtils::enDateCompare DateUtils::CompareDates(DateUtils Date1, DateUtils Date2)
{
    if (IsDate1BeforeDate2(Date1, Date2))
        return enDateCompare::Before;

    if (IsDate1EqualDate2(Date1, Date2))
        return enDateCompare::Equal;

    return enDateCompare::After;
}

// Compares current date with Date2
DateUtils::enDateCompare DateUtils::CompareDates(DateUtils Date2)
{
    return CompareDates(*this, Date2);
}

// Calculates age in days from date of birth to today
short DateUtils::CalculateMyAgeInDays(DateUtils DateOfBirth) {
    return GetDifferenceInDays(DateOfBirth, DateUtils::GetSystemDate(), true);
}

// Static: returns difference in days between two dates
int DateUtils::GetDifferenceInDays(DateUtils Date1, DateUtils Date2, bool IncludeEndDay)
{
    //this will take care of negative diff
    int Days = 0;
    short SawpFlagValue = 1;

    if (!IsDate1BeforeDate2(Date1, Date2))
    {
        //Swap Dates 
        SwapDates(Date1, Date2);
        SawpFlagValue = -1;

    }

    while (IsDate1BeforeDate2(Date1, Date2))
    {
        Days++;
        Date1 = AddOneDay(Date1);
    }

    return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
}

// Returns difference in days between current date and Date2
int DateUtils::GetDifferenceInDays(DateUtils Date2, bool IncludeEndDay) {
    return GetDifferenceInDays(*this, Date2, IncludeEndDay);
}