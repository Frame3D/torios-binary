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
 * Authors: James Dean Palmer <james@tiger-marmalade.com>
 *          2016-2018  djcj   <djcj@gmx.de> (modified for fltk-dialog)
 *          2019       Israel <israeldahl@gmail.com> (modified into single header)
 */

#ifndef _FL_CALENDAR_H_
#define _FL_CALENDAR_H_

#include <FL/Enumerations.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Repeat_Button.H>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "FDate.H"

#define FL_CALENDAR_COLOR      fl_lighter(FL_GRAY)
#define FL_CALENDAR_COLOR2     fl_darker(FL_GRAY)
#define FL_CALENDAR_LABELSIZE  12

static void fl_calendar_prv_month_cb (Fl_Widget *, void *b);
static void fl_calendar_nxt_month_cb (Fl_Widget *, void *b);
static void fl_calendar_prv_year_cb (Fl_Widget *, void *b);
static void fl_calendar_nxt_year_cb (Fl_Widget *, void *b);
static void fl_calendar_button_cb (Fl_Widget *a, void *b);
static const char *int_to_str (int n);
static char date[512] = {0};
static bool arabic_ = false;

/** @package libflek_ui
 * Fl_Calendar_Base is a widget that allows a user to select a date
 * (day, month, and year) with a wall style calendar.
 */
class Fl_Calendar_Base : public Fl_Group, public FDate
{
 protected:

  Fl_Button * days[7*6];
  Fl_Box * weeknumbers[6];
  Fl_Box * weekdays[7];
  Fl_Box * caption_m;
  Fl_Box * caption_y;
  Fl_Box * container_box;
  Fl_Repeat_Button * nxt_month;
  Fl_Repeat_Button * prv_month;
  Fl_Repeat_Button * nxt_year;
  Fl_Repeat_Button * prv_year;
  int selected_day_;
  int label_size_;
  Fl_Boxtype box_type_;
  int label_color_;
  int bg_color_;
  int bg_color_2_;
  std::string m_date_string;

public:

  /**
   * The constructor for an empty Fl_Calendar_Base.
   */
  Fl_Calendar_Base (int x, int y, int w = (7 * 20), int h = (6 * 20), const char *l = 0)
  : Fl_Group (x, y, w, h, l), FDate ()
  {
      label_size_  = FL_CALENDAR_LABELSIZE;
      box_type_    = FL_FLAT_BOX;
      label_color_ = FL_BLACK;
      bg_color_    = 255;
      bg_color_2_  = 1172889856;

      for (int i = 0; i < (7 * 6); i++)
      {

        days[i] = new Fl_Button (
                                  (w / 8) * (i % 7) + x + (w / 8),
                                  (h / 6) * (i / 7) + y,
                                  (w / 8),
                                  (h / 6)
                                 );

         days[i]->labelsize (label_size_);
         days[i]->down_box (box_type_);
         days[i]->box (box_type_);
         days[i]->color (bg_color_);
         days[i]->clear_visible_focus ();
      }
     // update();
  }

  void update_style()
  {
      container_box->box (box_type_);
      container_box->color (bg_color_2_);
      for (int i = 0; i < 7; i++)
      {
          weekdays[i]->box (box_type_);
          weekdays[i]->labelsize (label_size_);
          weekdays[i]->labelcolor(label_color_);
          weekdays[i]->color (bg_color_2_);
      }
      for (int i = 0; i < 6; i++)
      {
          weeknumbers[i]->box (box_type_);
          weeknumbers[i]->labelsize (label_size_);
          weeknumbers[i]->labelcolor(label_color_);
          weeknumbers[i]->color (bg_color_2_);
      }
      prv_month->box (box_type_);
      prv_month->down_box (box_type_);
      prv_month->labelsize (label_size_ + 1);
      caption_m->box (box_type_);
      caption_m->labelfont (FL_HELVETICA_BOLD);
      caption_m->labelsize (label_size_);
      nxt_month->box (box_type_);
      nxt_month->down_box (box_type_);
      nxt_month->labelsize (label_size_ + 1);
      nxt_year->box (box_type_);
      nxt_year->down_box (box_type_);
      nxt_year->labelsize (label_size_ + 1);
      caption_y->box (box_type_);
      caption_y->labelfont (FL_HELVETICA_BOLD);
      caption_y->labelsize (label_size_);
      prv_year->box (box_type_);
      prv_year->down_box (box_type_);
      prv_year->labelsize (label_size_ + 1);
  }


  void update ()
  {
    int dow = day_of_week (year (), month (), 0);
    int dim = days_in_month (month (), leap_year (year ()));
    int i, j, n, wk[6][3];

    int dipm_month;  /* previous month */
    int dipm_year;   /* year of previous month */

    if (month () == JANUARY)
    {
        dipm_month = DECEMBER;
        dipm_year  = year () - 1;
    }
    else
    {
        dipm_month = month () - 1;
        dipm_year  = year ();
    }

    int dipm = days_in_month (dipm_month, dipm_year);

  /* last days of previous month */
    for (i = 0; i < dow; i++)
    {
        days[i]->copy_label (int_to_str (i-dow+dipm+1));
        days[i]->color (bg_color_);
        days[i]->selection_color (bg_color_);
        days[i]->labelcolor (fl_darker(FL_WHITE));
        days[i]->callback (fl_calendar_prv_month_cb, this);
        days[i]->show ();
        days[i]->redraw();
    }

  /* current month */
    for (i = dow, j = 0; i < (dim + dow); i++)
    {
        n = i + 1 - dow;
        if (n == 1 || i % 7 == 0)
        {
            wk[j][0] = n;
            wk[j][1] = month ();
            wk[j][2] = year ();
            j++;
        }

        days[i]->copy_label (int_to_str (n));
        days[i]->color (bg_color_);
        days[i]->selection_color (bg_color_2_);
        days[i]->labelcolor(label_color_);

        if ( (i - dow + 1) == day () )
        {
            days[i]->color (bg_color_2_);
        }

        days[i]->callback (fl_calendar_button_cb, this);
        days[i]->show ();
        days[i]->redraw();
    }

  /* first days of next month */
    for (i = dim + dow; i < (6*7); i++)
    {
        n = i + 1 - dow - dim;

        if (i % 7 == 0)
        {
            wk[j][0] = n;

            if (month () == DECEMBER)
            {
                wk[j][1] = JANUARY;
                wk[j][2] = year () + 1;
            }
            else
            {
                wk[j][1] = month () + 1;
                wk[j][2] = year ();
            }

          j++;
        }

        days[i]->copy_label (int_to_str (n));
        days[i]->color (bg_color_);
        days[i]->selection_color (bg_color_);
        days[i]->labelcolor (fl_darker(FL_WHITE));
        days[i]->callback (fl_calendar_nxt_month_cb, this);
        days[i]->show ();
        days[i]->redraw();
      }

      for (i = 0, n = 53; i < 6; i++, n++)
      {
          if (n == 53)
          {
              n = iso_week_number(wk[i][2], wk[i][1], wk[i][0]);
          }
          else if (n > 53)
          {
              n = 1;
          }
          weeknumbers[i]->copy_label (int_to_str (n));
      }
      update_style();
  }

  /**
   * Resize the buttons contained in Fl_Calendar_Base to
   * fit in the passed dimensions.
   *
   * @param cx The calendar x position.
   * @param cy The calendar y position.
   * @param cw The calendar width.
   * @param ch The calendar height.
   */
  void csize (int cx, int cy, int cw, int ch)
  {
      for (int i = 0; i < (7 * 6); i++)
      {
          days[i]->resize (
                            (cw / 8) * (i % 7) + cx + (cw / 8),
                            (ch / 6) * (i / 7) + cy,
                            (cw / 8),
                            (ch / 6)
                           );
      }
  }

  /**
   * Returns a pointer to the button for the day D in the Fl_Calendar.
   */
  Fl_Button * day_button (int i)
  {
      if ((i > 0) && (i <= days_in_month ()))
      {
          return days[i + day_of_week (year (), month (), 0) - 1];
      }
      return 0;
  }

};

/**
 * Fl_Calendar is a subclass of Fl_Calendar.  This widget adds
 * day labels and controllers to the base calendar class.
 * <p><img src="Fl_Calendar.png">
 */
class Fl_Calendar : public Fl_Calendar_Base
{

 public:

  /**
   * The constructor for an empty Fl_Calendar.
   */
  Fl_Calendar (int x, int y, int w = (7*20), int h = (8*20), const char *l = 0)
   : Fl_Calendar_Base (x, y, w, h, l)
  {
      int title_height = h / 8;
      int h2           = (h - title_height) / 7;
      selected_day_    = 0;
      label_size_      = FL_CALENDAR_LABELSIZE;
      box_type_        = FL_FLAT_BOX;
      label_color_     = FL_BLACK;
      bg_color_    = 255;
      bg_color_2_  = 80;
      today();

      container_box = new Fl_Box(
                                 x,
                                 h2 * (1 / 8) + y + title_height,
                                 (w / 8),
                                 h2
                               );
      container_box->box (box_type_);
      container_box->color (bg_color_2_);

      for (int i = 0; i < 7; i++)
      {
          weekdays[i] = new Fl_Box ( 
                                      ( (w / 8) * ((i + 1) %8) + x),
                                      h2*((i+1) / 8) + y + title_height,
                                      (w / 8),
                                      h2
                                    );

          weekdays[i]->box (box_type_);
          weekdays[i]->labelsize (label_size_);
          weekdays[i]->labelcolor(label_color_);
          weekdays[i]->color (bg_color_2_);
      }

      weekdays[0]->label (fdate_mo);
      weekdays[1]->label (fdate_tu);
      weekdays[2]->label (fdate_we);
      weekdays[3]->label (fdate_th);
      weekdays[4]->label (fdate_fr);
      weekdays[5]->label (fdate_sa);
      weekdays[6]->label (fdate_su);

      for (int i = 0; i < 6; i++)
      {
          weeknumbers[i] = new Fl_Box (
                                         x,
                                         h2 + (i * h2) + y + title_height,
                                         (w / 8),
                                         h2
                                       );

          weeknumbers[i]->box (box_type_);
          weeknumbers[i]->labelsize (label_size_);
          weeknumbers[i]->labelcolor(label_color_);
          weeknumbers[i]->color (bg_color_2_);
      }

  /*  « MONTH »  */

      prv_month = new Fl_Repeat_Button (x, y, (w / 16), (h / 8), "@<<");
      prv_month->box (box_type_);
      prv_month->down_box (box_type_);
      prv_month->labelsize (label_size_ + 1);
      prv_month->callback (fl_calendar_prv_month_cb, this);
      prv_month->clear_visible_focus ();

      caption_m = new Fl_Box (x + (w / 16), y, ((w / 8) * 3), (h / 8));
      caption_m->box (box_type_);
      caption_m->labelfont (FL_HELVETICA_BOLD);
      caption_m->labelsize (label_size_);

      nxt_month = new Fl_Repeat_Button (
                                         (caption_m->x() + caption_m->w()),
                                         y,
                                         (w / 16),
                                         (h / 8),
                                         "@>>"
                                       );
      nxt_month->box (box_type_);
      nxt_month->down_box (box_type_);
      nxt_month->labelsize (label_size_ + 1);
      nxt_month->callback (fl_calendar_nxt_month_cb, this);
      nxt_month->clear_visible_focus ();

  /*  « YEAR »  */

      nxt_year = new Fl_Repeat_Button (
                                        (x + (w / 16) * 15),
                                        y,
                                        (w / 16),
                                        (h / 8),
                                        "@>>"
                                      );
      nxt_year->box (box_type_);
      nxt_year->down_box (box_type_);
      nxt_year->labelsize (label_size_ + 1);
      nxt_year->callback (fl_calendar_nxt_year_cb, this);
      nxt_year->clear_visible_focus ();

      caption_y = new Fl_Box (
                               (nxt_year->x() - (w / 16) * 4),
                               y,
                               (w / 16) * 4,
                               (h / 8)
                             );
      caption_y->box (box_type_);
      caption_y->labelfont (FL_HELVETICA_BOLD);
      caption_y->labelsize (label_size_);

      prv_year = new Fl_Repeat_Button (
                                        (caption_y->x() - (w / 16)),
                                        y,
                                        w / 16,
                                        h / 8,
                                        "@<<"
                                      );
      prv_year->box (box_type_);
      prv_year->down_box (box_type_);
      prv_year->labelsize (label_size_ + 1);
      prv_year->callback (fl_calendar_prv_year_cb, this);
      prv_year->clear_visible_focus ();

      Fl_Calendar_Base::csize (
                                x,
                                y + title_height + (h - title_height) / 7,
                                w,
                                h - title_height - (h - title_height) / 7
                              );
      Fl_Calendar_Base::update (); //why do I need to do this so many times?  what is wrong?
      update ();
      //update ();
      set_date_string();
  }
  char *format_date()
  {
      struct tm time;
      std::string format = "%e-%b-%Y";

      snprintf(date, sizeof(date), "%d-%d-%d", year(), month(), day());
      memset(&time, 0, sizeof(struct tm));
      strptime(date, "%Y-%m-%d", &time);
      strftime(date, sizeof(date), format.c_str(), &time);

      return  date;
  }
  void set_date_string()
  {
      m_date_string = format_date();
  }
  std::string get_date_string()
  {
    return m_date_string;
  }
  /**
   * Sets the value of the widget back by one month.
   */
  void previous_month ()
  {
      FDate::previous_month();
      update();
  }

  /**
   * Sets the value of the widget forward by one month.
   */
  void next_month ()
  {
      FDate::next_month();
      update();
  }

  /**
   * Sets the value of the widget back by one year.
   */
  void previous_year ()
  {
      FDate::previous_year();
      update();
  }

  /**
   * Sets the value of the widget forward by one year.
   */
  void next_year ()
  {
      FDate::next_year();
      update();
  }

  /**
   * Updates the widget after values have been changed.
   */
  void update ()
  {
      const char *_month_name[] =
      {
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

        Fl_Calendar_Base::update ();

        caption_m->copy_label (_month_name[month ()-1]);
        caption_m->redraw();
        std::string tmp = int_to_str (year ());
        caption_y->copy_label (tmp.c_str());
        caption_y->redraw();
        redraw ();

  }

  int  handle (int event)
  {
      int m, d, y, o, md;
      o = 0;

      switch (event)
      {
          case FL_FOCUS:
          case FL_UNFOCUS:
              return 1;

          case FL_KEYBOARD:
              m = month ();
              d = day ();
              y = year ();
              switch(Fl::event_key ())
              {
       /***
        case FL_Enter:
        selected_day_ = d;
        do_callback(this, d);
        break;
        ***/
                case FL_Up:
                    o = -7;
                    break;
                case FL_Down:
                    o = 7;
                    break;
                case FL_Right:
                    o = 1;
                    break;
                case FL_Left:
                    o = -1;
                    break;
                case FL_Page_Up:
                    previous_month ();
                    return 1;
                case FL_Page_Down:
                    next_month ();
                    return 1;
                default:
                    return Fl_Group::handle (event);
              }

              if (valid (y, m, d + o))
              {
                set_date (y, m, d + o);
              }
              else
              {
                  if (o < 0)
                  {
                      previous_month ();
                      m = month ();
                      y = year ();
                      md = days_in_month (m, leap_year (y));
                      //d = d + o + md;
                      d = md;
                      set_date (y, m, d);
                  }
                  else
                  {
                      next_month ();
                      m = month ();
                      y = year ();
                      md = days_in_month (m, leap_year (y));
                      //d = d + o - md;
                      d = 1;
                      set_date (y, m, d);
                  }
              }
              update ();
              return 1;  /* case FL_KEYBOARD */
      }  /* switch (event) */
      return Fl_Group::handle (event);
  }

  /**
   * Sets the Calendar's selection color.
   *
   * @param color The calendar's selection color.
   */
  //void selection_color (Fl_Color c);

  /**
   * Gets the Calendar's selection color.
   *
   * @return The calendar's selection color.
   */
  //Fl_Color selection_color() const {
  //  return Fl_Group::selection_color();
  //}

  /**
   * Gets the user selected day.  This method differs
   * from the day() method in that if a user has not
   * selected a day the return value is zero.
   *
   * @return The selected day if the user has selected a day, 0 otherwise.
   */
  int selected_day() {return selected_day_;}

  /**
   * Sets the user selected day.  If d is non zero, this
   * method also sets the day.
   *
   * @return The selected day if the user has selected a day, 0 otherwise.
   */
  int selected_day(int d)
  {
      selected_day_ = d;

      if (d)
      {
          day(d);
      }

      return d;
  }

  /**
   * Set non-zero to enable Eastern Arabic numbers.
   */
  void arabic (int i)
  {
    arabic_ = (i == 0) ? false : true;
    update();
  }
  int arabic () {return arabic_ ? 1 : 0;}
  void bg_color_2 (int i){ bg_color_2_=i; }
  int bg_color_2(){ return bg_color_2_; }
  void bg_color(int i){ bg_color_=i; }
  int bg_color(){ return bg_color_; }
  void label_color(int i){ label_color_=i; }
  int label_color(){ return label_color_; }
  void box_type(Fl_Boxtype i){ box_type_=i; }
  Fl_Boxtype box_type(){ return box_type_; }
  void label_size(int i){ label_size_=i; }
  int label_size(){ return label_size_; }

};

static void fl_calendar_prv_month_cb (Fl_Widget *, void *b)
{
    Fl_Calendar *c = reinterpret_cast<Fl_Calendar *>(b);
    c->previous_month ();
    c->do_callback(c, 0L);
}

static void fl_calendar_nxt_month_cb (Fl_Widget *, void *b)
{
    Fl_Calendar *c = reinterpret_cast<Fl_Calendar *>(b);
    c->next_month ();
    c->do_callback(c, 0L);
}

static void fl_calendar_prv_year_cb (Fl_Widget *, void *b)
{
    Fl_Calendar *c = reinterpret_cast<Fl_Calendar *>(b);
    c->previous_year ();
    c->do_callback(c, 0L);
}

static void fl_calendar_nxt_year_cb (Fl_Widget *, void *b)
{
    Fl_Calendar *c = reinterpret_cast<Fl_Calendar *>(b);
    c->next_year ();
    c->do_callback(c, 0L);
}

static void fl_calendar_button_cb (Fl_Widget *a, void *b)
{
    Fl_Button   *sb;

    long j         = 0;
    Fl_Calendar *c = reinterpret_cast<Fl_Calendar *>(b);
    int numdays    = c->days_in_month () + 1;

    for (int i = 1; i < numdays; i++)
    {
        sb = c->day_button(i);
        sb->color (c->bg_color());

        if (dynamic_cast<Fl_Button *>(a) == sb)
        {
            c->selected_day(i);
            c->update();
            c->set_date_string();
            j = i;
            sb->color (c->bg_color_2());
        }
    }
    c->redraw();
    c->do_callback(c, j);
}

static const char *int_to_str (int n)
{
    std::string s, zero = "0";
    int pos             = 0;

    if (arabic_)
    {
        zero = "\xD9\xA0";
        pos  = 1;
    }

    if (n == 0)
    {
        return zero.c_str();
    }

    while (n != 0)
    {
        std::string tmp  = s;
                      s  = zero + tmp;
                 s[pos] += n % 10;
                      n /= 10;
    }

    return s.c_str();
}

#endif
