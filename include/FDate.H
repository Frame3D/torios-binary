/*
 * Copyright 1999-2000 by the Flek development team.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Authors: David Freese
 *          2016, 2018  djcj <djcj@gmx.de>
 */

#ifndef __FDATE_H__
#define __FDATE_H__

#define DOE_MIN   1        /* January 1, 1 */
#define DOE_MAX   3652059  /* December 31, 9999 */
#define YEAR_MIN  1
#define YEAR_MAX  9999

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr const char *fdate_mo = "Mo";
constexpr const char *fdate_tu = "Tu";
constexpr const char *fdate_we = "We";
constexpr const char *fdate_th = "Th";
constexpr const char *fdate_fr = "Fr";
constexpr const char *fdate_sa = "Sa";
constexpr const char *fdate_su = "Su";

constexpr const char *fdate_mon_jan = "January";
constexpr const char *fdate_mon_feb = "Febuary";
constexpr const char *fdate_mon_mar = "March";
constexpr const char *fdate_mon_apr = "April";
constexpr const char *fdate_mon_may = "May";
constexpr const char *fdate_mon_jun = "June";
constexpr const char *fdate_mon_jul = "July";
constexpr const char *fdate_mon_aug = "August";
constexpr const char *fdate_mon_sep = "September";
constexpr const char *fdate_mon_oct = "October";
constexpr const char *fdate_mon_nov = "November";
constexpr const char *fdate_mon_dec = "December";
/**
 * An array of month names.
static const char* month_name[] = {
  fdate_mon_jan,
  fdate_mon_feb,
  fdate_mon_mar,
  fdate_mon_apr,
  fdate_mon_may,
  fdate_mon_jun,
  fdate_mon_jul,
  fdate_mon_aug,
  fdate_mon_sep,
  fdate_mon_oct,
  fdate_mon_nov,
  fdate_mon_dec
};
 */

/**
 * An array of days of the month for a non leap year, 1-12. (0 is ignored.)
 */
static const int days[] = { 0, 31, 28, 31, 30,  31,  30,  31,  31,  30,  31,  30, 31 };

/**
 * An array of total days since the beginning of the year for
 * each month, 1-12.  (0 is ignored.)
 */
static const int julian_days[2][13] = {
  { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
  { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
};
/**
 * from FBase.H
 */
class FBase
{
 public:
  typedef FBase *Ptr;
};

typedef enum {
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
} FWeekday;

typedef enum {
  JANUARY = 1,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
} FMonth;

/** @package libflek_core
 * FDate provides a date class that stores the day, month and year.
 */
class FDate : public FBase
{

 public:

  /**
   * Default constructor.
   */
  FDate(){ today(); }

  /**
   * Three argument constructor.  Initializes this object with the
   * year, month and day.
   *
   * @param y The year.
   * @param m The month.
   * @param d The day.
   */
  FDate (int y, int m, int d){ set_date (y, m, d); }

  /**
   * Copy constructor.
   *
   * @param src The FDate object to copy initial values from.
   */
  FDate (const FDate& dt){ set_date (dt); }

  /* (ScanDoc doesn't like this one)
   * Copy method.  This virtual method makes a new copy of this object.
   *
   * @return The pointer (FBase::Ptr) to the new FDate instance.
   */
  virtual FBase::Ptr copy () const {return new FDate (*this);}

  /**
   * Sets the date from the year, month, and day.
   *
   * @param y The year.
   * @param m The month, 1 through 12.
   * @param d The day, 1 through the numbers of days in that month.
   */
  void set_date (int y, int m, int d)
  {
      if (valid (y, m, d))
      {
          Year = y;
          Month = m;
          Day = d;
      }
      else
      {
          today ();
      }
  }

  /**
   * Sets the date value from another FDate object.
   *
   * @param src The FDate object to set values from.
   */
  void set_date (const FDate& dt)
  {
      Year = dt.Year;
      Month = dt.Month;
      Day = dt.Day;
  }

  /**
   * Set the date value to today's date.
   */
  void today ()
  {
      time_t t;
      struct tm *now;
      time (&t);
      now = localtime (&t);
      Year = now->tm_year + 1900;
      Month = now->tm_mon + 1;
      Day = now->tm_mday;
  }

  /**
   * Sets the year.
   *
   * @param y The year to associate with this object.
   */
  void year (int y) { Year = y; }

  /**
   * Gets the year.
   *
   * @return The year associated with this object.
   */
  int year (){ return Year; }

  /**
   * Sets the month.
   *
   * @param m The month to associate with this object.
   */
  void month (int m){ Month = m; }

  /**
   * Gets the month.
   *
   * @return The month associated with this object.
   */
  int  month (){ return Month; }

  /**
   * Sets the day.
   *
   * @param d The day of the month to associate with this object.
   */
  void day (int d){ Day = d; }

  /**
   * Gets the day.
   *
   * @return The day of the month associated with this object.
   */
  int day (){ return Day; }

  /**
   * Equality comparison of two dates.
   *
   * @param src The FDate object to compare this one to.
   * @return True if this object and src are equal.  False otherwise.
   */
  bool operator== (const FDate& d)
  {
      if (this->Year != d.Year) { return false; }
      if (this->Month != d.Month) { return false; }
      if (this->Day != d.Day) { return false; }
      return true;
  }

  /**
   * Inequality comparison of two dates.
   *
   * @param src The FDate object to compare this one to.
   * @return True if this object and src are <b>not</b> equal.  False otherwise.
   */
  bool operator!= (const FDate& d){return (!(*this == d));}

  /**
   * Comparison of two dates.
   *
   * @param src The FDate object to compare this one to.
   * @return True if this FDate object is less than the src object.  False otherwise.
   */
  bool operator< (const FDate& d)
  {
      if (this->Year < d.Year) { return true; }
      if (this->Year > d.Year) { return false; }
      if (this->Month < d.Month) { return true; }
      if (this->Month > d.Month) { return false; }
      if (this->Day < d.Day) { return true; }
      return false;
  }

  /**
   * Comparison of two dates.
   *
   * @param src The FDate object to compare this one to.
   * @return True if this FDate object is greater than the src object.  False otherwise.
   */
  bool operator> (const FDate& d)
  {
      if (*this < d) { return false; }
      if (*this == d) { return false; }
      return true;
  }

  /**
   * Sets one date equal to another date.
   *
   * @param src The FDate object to set values from.
   */
  void operator= (const FDate& d)
  {
      this->Year = d.Year;
      this->Month = d.Month;
      this->Day = d.Day;
  }

  /**
   * Adds days to the date.
   *
   * @param d The number of days to add to this date.
   */
  const FDate &operator+= (int d)
  {
      for (int i = 0; i < d; i++)
      {
        help_increment();
      }

      return *this;
  }

  /**
   * Pre-increment operator.  Increment the date by one day.
   */
  FDate &operator++ ()
  {
      help_increment ();
      return *this;
  }

  /**
   * Post-increment operator. Increment the date by one day.
   */
  FDate operator++ (int)
  {
      FDate temp = *this;
      help_increment ();
      return temp;
  }

  /**
   * Gets wether day d is at the end of the month.
   *
   * @param d The day to check.
   * @return True if d is at the end of the month.  False otherwise.
   */
  bool end_of_month (int d)
  {
      if (Month == 2 && leap_year (Year))
      {
          return (d == 29);  /* last day of Feb in leap year */
      }
      else
      {
          return (d == days[Month]);
      }
  }

  /**
   * Gets weather year y is a leap year.
   *
   * @param y The year to check.
   * @return True if the year is a leap year.  False otherwise.
   */
  static bool leap_year (int y)
  {
      if (y % 400 == 0 || ( y % 100 != 0 && y % 4 == 0 ))
      {
          return true;
      }
      return false;
  }

  /**
   * Gets wether the year associated with this object is a leap year.
   *
   * @return True if the year is a leap year.  False otherwise.
   */
  bool leap_year () { return leap_year (Year); }

  /**
   * Gets wether the passed date is valid.
   *
   * @param y The year.
   * @param m The month, 1 through 12.
   * @param d The day, 1 through the numbers of days in that month.
   * @return True if the year, month and day make a valid date.  False otherwise.
   */
  static bool valid (int y, int m, int d)
  {
      if (y < YEAR_MIN || y > YEAR_MAX) { return false; }

      if (m < 1 || m > 12) { return false; }

      if (d < 1 ) { return false; }

      if (leap_year (y))
      {
          if ((m == 2) && (d > 29))
          {
            return false;
          }
          else
          {
            return true;
          }
      }

      if (d > days[m])
      {
          return false;
      }

      return true;
  }

  /**
   * Gets wether the current date is valid.
   *
   * @return True if the year, month and day make a valid date.  False otherwise.
   */
  bool valid () { return valid (Year, Month, Day); }

  /**
   * Gets the number of days in the month for a given month and leap value.
   *
   * @param m The month, 1 through 12.
   * @param leap Should be 1 if the associated year is a leap year, 0 otherwise.
   * @return The number of days in the month.
   */
  static int days_in_month (int month, int leap)
  {
      /* Validate the month. */
      if (month < JANUARY || month > DECEMBER)
      {
          return -1;
      }

      /* Return 28, 29, 30, or 31 based on month/leap. */
      if (month == FEBRUARY)
      {
          return leap ? 29 : 28;
      }
      return days[month];
  }

  /**
   * Gets the number of days in the month for this date.
   *
   * @return The number of days in the month.
   */
  int days_in_month () { return days_in_month (Month, leap_year (Year)); }

  /**
   * Gets the day of the year for the passed date.
   *
   * @param y The year.
   * @param m The month, 1 through 12.
   * @param d The day, 1 through the numbers of days in that month.
   * @return The day of the year.
   */
  static int day_of_year (int year, int month, int day){ return day + julian_days[leap_year (year) ? 1 : 0][month]; }

  /**
   * Gets the day of the year for this date.
   *
   * @return The day of the year.
   */
  int day_of_year() { return day_of_year (Year, Month, Day); }

  /**
   * Gets the day of the epoch for the passed date.
   *
   * @param y The year.
   * @param m The month, 1 through 12.
   * @param d The day, 1 through the numbers of days in that month.
   * @return The day of the epoch.
   */
  static int day_of_epoch (int year, int month, int day)
  {
    int doe, era, cent, quad, rest;

  /* break down the year into 400, 100, 4, and 1 year multiples */
    rest = year - 1;

    quad = rest / 4;
    rest %= 4;

    cent = quad / 25;
    quad %= 25;

    era = cent / 4;
    cent %= 4;

  /* set up doe */
    doe = day_of_year (year, month, day);
    doe += era * (400 * 365 + 97);
    doe += cent * (100 * 365 + 24);
    doe += quad * (4 * 365 + 1);
    doe += rest * 365;

    return doe;
  }

  /**
   * Gets the day of the epoch for this date.
   *
   * @return The day of the epoch.
   */
  int day_of_epoch() { return day_of_epoch (Year, Month, Day); }

  /**
   * Gets the day of the week for the passed date.
   *
   * @param y The year.
   * @param m The month, 1 through 12.
   * @param d The day, 1 through the numbers of days in that month.
   * @return The day of the week, 1 through 7.
   */
  static int day_of_week (int year, int month, int day){ return day_of_epoch (year, month, day) % 7; }

  /**
   * Gets the day of the week for this date.
   *
   * @return The day of the week, 1 through 7.
   */
  int day_of_week() { return day_of_week (Year, Month, Day); }

  static int iso_week_number (int year, int month, int day)
  {
    struct tm time;
    char tmp[16];
    char wn[8];

    memset(&time, 0, sizeof(struct tm));
    sprintf(tmp, "%d %d %d", year, month, day);
    strptime(tmp, "%Y %m %d", &time);
    strftime(wn, sizeof(wn), "%-V", &time);
    return atoi(wn);
  }

  /**
   * Decrement the date by one month.
   */
  void previous_month ()
  {
      if (Month == 1)
      {
          Month = 12;
          Year--;
      }
      else
      {
          Month--;
      }
      while (Day > days_in_month (Month, leap_year (Year)))
      {
         Day--;
      }
  }

  /**
   * Increment the date by one month.
   */
  void next_month ()
  {
     if (Month == 12)
     {
         Month = 1;
         Year++;
     }
     else
     {
         Month++;
     }

     while (Day > days_in_month (Month, leap_year (Year)))
     {
         Day--;
     } 
  }

  /**
   * Decrement the date by one year.
   */
  void previous_year ()
  {
      if (Month == 2 && Day == 29)
      {
          Day = 28;
      }
      Year--;
  }

  /**
   * Increment the date by one year.
   */
  void next_year ()
  {
      if (Month == 2 && Day == 29)
      {
          Day = 28;
      }
      Year++;
  }

private:

  int  Year;
  int  Month;
  int  Day;
  void help_increment ()
  {
      if (end_of_month (Day) && Month == 12)
      {  /* end year */
          Day = 1;
          Month = 1;
          ++Year;
      }
      else if (end_of_month (Day))
      {
          Day = 1;
          ++Month;
      }
      else
      {
          ++Day;
      }
  }

};

#endif