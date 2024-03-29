// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef StaticText_h
#define StaticText_h
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

class StaticText : public Fl_Widget {
  enum {MaxLength = 255}; 
  char *str; 
public:
  StaticText(int xx,int yy,int ww,int hh) ;
  ~StaticText();
  void value(const char *mstr);
private:
  void draw();
};
#endif
