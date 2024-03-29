// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef flpower_h
#define flpower_h
#include <FL/Fl.H>
#include "../include/functions.h"
#include "../include/single.h"
#include "../include/toolbar_icons.h"
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_XBM_Image.H>
#include <FL/Fl_XPM_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/sendfile.h>  // sendfile
#include <algorithm>
#include <float.h>
#include <sstream>
#include <float.h>
#include <dirent.h>
#include <sys/stat.h>
#include <langinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <locale.h>
#include <unistd.h>
#include <signal.h>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

class UI {
protected:
  unsigned int type; 
  std::string SHUTDOWN_TEXT; 
  std::string REBOOT_TEXT; 
  std::string SUSPEND_TEXT; 
  std::string HIBERNATE_TEXT; 
  std::string LOGOUT_TEXT; 
public:
  UI();
  Fl_Double_Window* make_window();
  Fl_Double_Window *win;
private:
  inline void cb_OK_i(Fl_Button*, void*);
  static void cb_OK(Fl_Button*, void*);
  inline void cb_Cancel_i(Fl_Button*, void*);
  static void cb_Cancel(Fl_Button*, void*);
public:
  Fl_Box *icon;
  Fl_Box *label;
  void decide();
  int hibernate();
  int leave();
  void setup(int TYPE,bool YES);
  int shutdown();
  int restart();
  int suspend();
};
int main(int argc, char *argv[]);
int usage(char* name);
#endif
