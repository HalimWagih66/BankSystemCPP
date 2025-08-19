#pragma once

#include<iostream>
#include<string>

class DateUtils
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;

public:
    // Constructors
    DateUtils();
    DateUtils(std::string sDate); // Accepts string like "dd/mm/yyyy"
    DateUtils(short Day, short Month, short Year);
    DateUtils(short DateOrderInYear, short Year);

    // Day property
    void SetDay(short Day);
    short GetDay();
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    // Month property
    void SetMonth(short Month);
    short GetMonth();
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    // Year property
    void SetYear(short Year);
    short GetYear();
    __declspec(property(get = GetYear, put = SetYear)) short Year;

    // Print date in standard format
    void Print();

    // System date utilities
    static DateUtils GetSystemDate();
    static std::string GetSystemDateTimeString();

    // Validation
    static bool IsValidDate(DateUtils Date);
    bool IsValid();

    // Date formatting
    static std::string DateToString(DateUtils Date);
    std::string DateToString();

    // Leap year and year info
    static bool isLeapYear(short Year);
    bool isLeapYear();
    static short NumberOfDaysInAYear(short Year);
    short NumberOfDaysInAYear();
    static short NumberOfHoursInAYear(short Year);
    short NumberOfHoursInAYear();
    static int NumberOfMinutesInAYear(short Year);
    int NumberOfMinutesInAYear();
    static int NumberOfSecondsInAYear(short Year);
    int NumberOfSecondsInAYear();

    // Month utilities
    static short NumberOfDaysInAMonth(short Month, short Year);
    short NumberOfDaysInAMonth();
    static short NumberOfHoursInAMonth(short Month, short Year);
    short NumberOfHoursInAMonth();
    static int NumberOfMinutesInAMonth(short Month, short Year);
    int NumberOfMinutesInAMonth();
    static int NumberOfSecondsInAMonth(short Month, short Year);
    int NumberOfSecondsInAMonth();

    // Week utilities
    static short DayOfWeekOrder(short Day, short Month, short Year);
    short DayOfWeekOrder();
    static std::string DayShortName(short DayOfWeekOrder);
    static std::string DayShortName(short Day, short Month, short Year);
    std::string DayShortName();

    // Month name utilities
    static std::string MonthShortName(short MonthNumber);
    std::string MonthShortName();

    // Calendar display
    static void PrintMonthCalendar(short Month, short Year);
    void PrintMonthCalendar();
    static void PrintYearCalendar(int Year);
    void PrintYearCalendar();

    // Day calculations
    static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year);
    short DaysFromTheBeginingOfTheYear();

    static DateUtils GetDateFromDayOrderInYear(short DateOrderInYear, short Year);

    // Increase date
    void AddDays(short Days);
    static DateUtils AddOneDay(DateUtils Date);
    void AddOneDay();
    static void SwapDates(DateUtils& Date1, DateUtils& Date2);

    // Comparison
    static bool IsDate1BeforeDate2(DateUtils Date1, DateUtils Date2);
    bool IsDateBeforeDate2(DateUtils Date2);
    static bool IsDate1EqualDate2(DateUtils Date1, DateUtils Date2);
    bool IsDateEqualDate2(DateUtils Date2);
    static bool IsLastDayInMonth(DateUtils Date);
    bool IsLastDayInMonth();
    static bool IsLastMonthInYear(short Month);

    // Increase by units
    static DateUtils IncreaseDateByOneWeek(DateUtils& Date);
    void IncreaseDateByOneWeek();
    DateUtils IncreaseDateByXWeeks(short Weeks, DateUtils& Date);
    void IncreaseDateByXWeeks(short Weeks);
    DateUtils IncreaseDateByOneMonth(DateUtils& Date);
    void IncreaseDateByOneMonth();
    DateUtils IncreaseDateByXDays(short Days, DateUtils& Date);
    void IncreaseDateByXDays(short Days);
    DateUtils IncreaseDateByXMonths(short Months, DateUtils& Date);
    void IncreaseDateByXMonths(short Months);
    static DateUtils IncreaseDateByOneYear(DateUtils& Date);
    void IncreaseDateByOneYear();
    DateUtils IncreaseDateByXYears(short Years, DateUtils& Date);
    void IncreaseDateByXYears(short Years);
    DateUtils IncreaseDateByOneDecade(DateUtils& Date);
    void IncreaseDateByOneDecade();
    DateUtils IncreaseDateByXDecades(short Decade, DateUtils& Date);
    void IncreaseDateByXDecades(short Decade);
    DateUtils IncreaseDateByOneCentury(DateUtils& Date);
    void IncreaseDateByOneCentury();
    DateUtils IncreaseDateByOneMillennium(DateUtils& Date);
    DateUtils IncreaseDateByOneMillennium();

    // Decrease by units
    static DateUtils DecreaseDateByOneDay(DateUtils Date);
    void DecreaseDateByOneDay();
    static DateUtils DecreaseDateByOneWeek(DateUtils& Date);
    void DecreaseDateByOneWeek();
    static DateUtils DecreaseDateByXWeeks(short Weeks, DateUtils& Date);
    void DecreaseDateByXWeeks(short Weeks);
    static DateUtils DecreaseDateByOneMonth(DateUtils& Date);
    void DecreaseDateByOneMonth();
    static DateUtils DecreaseDateByXDays(short Days, DateUtils& Date);
    void DecreaseDateByXDays(short Days);
    static DateUtils DecreaseDateByXMonths(short Months, DateUtils& Date);
    void DecreaseDateByXMonths(short Months);
    static DateUtils DecreaseDateByOneYear(DateUtils& Date);
    void DecreaseDateByOneYear();
    static DateUtils DecreaseDateByXYears(short Years, DateUtils& Date);
    void DecreaseDateByXYears(short Years);
    static DateUtils DecreaseDateByOneDecade(DateUtils& Date);
    void DecreaseDateByOneDecade();
    static DateUtils DecreaseDateByXDecades(short Decades, DateUtils& Date);
    void DecreaseDateByXDecades(short Decades);
    static DateUtils DecreaseDateByOneCentury(DateUtils& Date);
    void DecreaseDateByOneCentury();
    static DateUtils DecreaseDateByOneMillennium(DateUtils& Date);
    void DecreaseDateByOneMillennium();

    // Week/day utilities
    static short IsEndOfWeek(DateUtils Date);
    short IsEndOfWeek();
    static bool IsWeekEnd(DateUtils Date);
    bool IsWeekEnd();
    static bool IsBusinessDay(DateUtils Date);
    bool IsBusinessDay();
    static short DaysUntilTheEndOfWeek(DateUtils Date);
    short DaysUntilTheEndOfWeek();
    static short DaysUntilTheEndOfMonth(DateUtils Date1);
    short DaysUntilTheEndOfMonth();
    static short DaysUntilTheEndOfYear(DateUtils Date1);
    short DaysUntilTheEndOfYear();

    // Date diff and vacation


    static int GetDifferenceInDays(DateUtils Date1, DateUtils Date2, bool IncludeEndDay = false);
    int GetDifferenceInDays(DateUtils Date2, bool IncludeEndDay = false);
    static short CalculateMyAgeInDays(DateUtils DateOfBirth);
    static short CalculateBusinessDays(DateUtils DateFrom, DateUtils DateTo);
    static short CalculateVacationDays(DateUtils DateFrom, DateUtils DateTo);
    static DateUtils CalculateVacationReturnDate(DateUtils DateFrom, short VacationDays);

    static bool IsDate1AfterDate2(DateUtils Date1, DateUtils Date2);
    bool IsDateAfterDate2(DateUtils Date2);

    // Enum for comparing two dates
    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    static enDateCompare CompareDates(DateUtils Date1, DateUtils Date2);
    enDateCompare CompareDates(DateUtils Date2);
};
