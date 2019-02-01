// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef flscreenie_h
#define flscreenie_h
#include <FL/Fl.H>
#include "../include/single.h"
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_File_Chooser.H>
#include <string>
#include <fstream>
#include <iostream>
#include <FL/fl_draw.H>
#include <png.h>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

class UI {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *screener_win;
private:
  inline void cb_Full_i(Fl_Button*, void*);
  static void cb_Full(Fl_Button*, void*);
  inline void cb_Quit_i(Fl_Button*, void*);
  static void cb_Quit(Fl_Button*, void*);
  inline void cb_Area_i(Fl_Button*, void*);
  static void cb_Area(Fl_Button*, void*);
public:
  void full_screen();
  void screenshot(int w, int h,int x=0,int y=0, bool FULL = true);
  Fl_Double_Window* sizer_window();
  Fl_Double_Window *s_win;
private:
  inline void cb_Take_i(Fl_Button*, void*);
  static void cb_Take(Fl_Button*, void*);
};
int main(int argc, char*argv[]);
void trace(std::string msg);
#include <FL/Fl_Scroll.H>

class Screenie : public Fl_Window {
protected:
  int X,Y; 
public:
  Screenie(int w, int h, const char* l = 0,int x=0, int y=0);
  void draw();
  void save_image(uchar *p,int w, int h);
  void save_file();
  Fl_Double_Window* preview_image();
  Fl_Double_Window *previewer_win;
  Fl_Box *previewer;
  Fl_Button *saver;
private:
  inline void cb_saver_i(Fl_Button*, void*);
  static void cb_saver(Fl_Button*, void*);
  inline void cb_Quit1_i(Fl_Button*, void*);
  static void cb_Quit1(Fl_Button*, void*);
public:
  int save_png(const char *file,unsigned char* p,int w,int h);
};
#endif
