// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef flapt_h
#define flapt_h
#include <FL/Fl.H>
#include <list>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
#include <dirent.h> //dir
#include <fstream> //ifstream
#include <fcntl.h> //readlink
#include <unistd.h> //readlink
#include <vector>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>

class UI {
protected:
  std::list<std::string> LIST; 
public:
  static bool compare_nocase(const std::string& first, const std::string& second);
  std::string file_to_string(std::string filename);
  void get_packages(Fl_Browser *o);
  std::string get_directory_from_filename(std::string filename);
  std::string get_symlinkpath(std::string symlink);
  Fl_Double_Window* make_window();
  Fl_Double_Window *about;
  Fl_Button *ok;
private:
  inline void cb_ok_i(Fl_Button*, void*);
  static void cb_ok(Fl_Button*, void*);
public:
  Fl_Browser *text;
  Fl_Button *installed;
private:
  inline void cb_installed_i(Fl_Button*, void*);
  static void cb_installed(Fl_Button*, void*);
public:
  void populateBrowserWithString(Fl_Browser *o, std::string STRING);
  bool test_file(std::string fileWithFullPATH);
};
int main(int argc, char*argv[]);
void trace(std::string msg);
#endif
