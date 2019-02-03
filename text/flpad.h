// copyright 2018 Israel Dahl
// GPL 3
// created from the FLTK tutorial using FLUID to design the UI
// created as part of the ToriOS project
// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef flpad_h
#define flpad_h
#include <FL/Fl.H>
#include <netinet/in.h>
#include "lexertk.hpp"
#include "../include/toolbar_icons.h"
#include <algorithm>
#include <sstream>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Printer.H>
#include <FL/fl_ask.H>
#include <FL/Fl_RGB_Image.H>
#include <errno.h>
#include <vector>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
int ret_val; 
std::string return_value; 
unsigned int EDIT_COLOR;
unsigned int NORMAL_COLOR; 
unsigned int FOREGROUND_TEXT;
unsigned int BACKGROUND_TEXT;
unsigned int SELECTION_TEXT;
unsigned int COMMENT_TEXT;
unsigned int STRING_TEXT;
unsigned int DIRECTIVE_TEXT;
unsigned int NUMBER_TEXT;
unsigned int KEYWORD_TEXT;
unsigned int TYPE_TEXT;
unsigned int SYMBOLS_TEXT;
unsigned int SPECIAL_TEXT;
unsigned int BROKEN_TEXT;
int FONT_TEXT;
int SIZE_TEXT;
int LINE_NUMBERS;
int BUTTON_COLOR;
int HIGHLIGHT_PLAIN; 
std::vector<std::string> SYNTAX_HEADERS; 
std::string SYNTAX_FILE; 

class Fl_Syntax_Text_Editor : public Fl_Text_Editor {
public:
  Fl_Syntax_Text_Editor(int x, int y, int w, int h, const char* label = 0);
  ~Fl_Syntax_Text_Editor();
  bool WRAPPED; 
  bool RELEASE; 
  Fl_Text_Display::Style_Table_Entry styletable[10]; 
  Fl_Text_Buffer * stylebuffer; 
  Fl_Text_Buffer * textbuffer; 
  std::string filename; 
  std::string search; 
  int changed; 
  int loading; 
  std::vector<std::string> KEYWORDS, TYPES; 
  std::string STYLE_HEADER; 
  lexertk::generator generator; 
  lexertk::helper::bracket_checker bracket_checker; 
  lexertk::helper::symbol_replacer symbol_replacer; 
  static void changed_cb(int, int nInserted, int nDeleted, int, const char*, void *v);
  std::string file_string();
  void get_styletable(Fl_Text_Display::Style_Table_Entry &styles,int which);
protected:
  int handle(int event);
public:
  void init_highlight();
  void modify_cb(int pos=0, int nInserted=0, int nDeleted=0, int unused=0, const char * nada=NULL);
  void refresh();
  void set_type(std::string fname);
  std::string style_line(std::string thisLine);
  static void style_update(int pos=0, int nInserted=0, int nDeleted=0, int unused=0, const char * nada=NULL, void *cbArg = NULL);
  static void style_unfinished_cb(int, void*);
  void theme_editor(unsigned int FG,unsigned int BG, unsigned int selection, int font, int size,int linenum );
  void update_styletable();
};
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Menu_Button.H>

class UI {
public:
  bool RELEASE; 
  UI();
  Fl_Double_Window* about_window();
  Fl_Double_Window *about_win;
private:
  inline void cb_Close_i(Fl_Button*, void*);
  static void cb_Close(Fl_Button*, void*);
public:
  void make_popup(Fl_Widget *o);
  Fl_Double_Window* make_replace();
  Fl_Double_Window *replace_dlg;
  Fl_Input *replace_find;
  Fl_Input *replace_with;
  Fl_Button *replace_cancel;
private:
  inline void cb_replace_cancel_i(Fl_Button*, void*);
  static void cb_replace_cancel(Fl_Button*, void*);
public:
  Fl_Button *replace_all;
private:
  inline void cb_replace_all_i(Fl_Button*, void*);
  static void cb_replace_all(Fl_Button*, void*);
public:
  Fl_Button *replace_next;
private:
  inline void cb_replace_next_i(Fl_Button*, void*);
  static void cb_replace_next(Fl_Button*, void*);
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *win;
  Fl_Menu_Bar *menu;
  static unsigned char menu_menu_i18n_done;
  static Fl_Menu_Item menu_menu[];
private:
  inline void cb_New_i(Fl_Menu_*, void*);
  static void cb_New(Fl_Menu_*, void*);
  inline void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
  inline void cb_Insert_i(Fl_Menu_*, void*);
  static void cb_Insert(Fl_Menu_*, void*);
  inline void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  inline void cb_Save1_i(Fl_Menu_*, void*);
  static void cb_Save1(Fl_Menu_*, void*);
  inline void cb_Exit_i(Fl_Menu_*, void*);
  static void cb_Exit(Fl_Menu_*, void*);
  inline void cb_Undo_i(Fl_Menu_*, void*);
  static void cb_Undo(Fl_Menu_*, void*);
  inline void cb_Cut_i(Fl_Menu_*, void*);
  static void cb_Cut(Fl_Menu_*, void*);
  inline void cb_Copy_i(Fl_Menu_*, void*);
  static void cb_Copy(Fl_Menu_*, void*);
  inline void cb_Paste_i(Fl_Menu_*, void*);
  static void cb_Paste(Fl_Menu_*, void*);
  inline void cb_Select_i(Fl_Menu_*, void*);
  static void cb_Select(Fl_Menu_*, void*);
  inline void cb_Preferences_i(Fl_Menu_*, void*);
  static void cb_Preferences(Fl_Menu_*, void*);
  inline void cb_Word_i(Fl_Menu_*, void*);
  static void cb_Word(Fl_Menu_*, void*);
  inline void cb_Find_i(Fl_Menu_*, void*);
  static void cb_Find(Fl_Menu_*, void*);
  inline void cb_F_i(Fl_Menu_*, void*);
  static void cb_F(Fl_Menu_*, void*);
  inline void cb_Replace_i(Fl_Menu_*, void*);
  static void cb_Replace(Fl_Menu_*, void*);
  inline void cb_Re_i(Fl_Menu_*, void*);
  static void cb_Re(Fl_Menu_*, void*);
  inline void cb_Go_i(Fl_Menu_*, void*);
  static void cb_Go(Fl_Menu_*, void*);
  inline void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
public:
  Fl_Group *buttons;
  Fl_Button *add_button;
private:
  inline void cb_add_button_i(Fl_Button*, void*);
  static void cb_add_button(Fl_Button*, void*);
public:
  Fl_Button *remove_button;
private:
  inline void cb_remove_button_i(Fl_Button*, void*);
  static void cb_remove_button(Fl_Button*, void*);
public:
  Fl_Button *open_button;
private:
  inline void cb_open_button_i(Fl_Button*, void*);
  static void cb_open_button(Fl_Button*, void*);
public:
  Fl_Button *save_button;
private:
  inline void cb_save_button_i(Fl_Button*, void*);
  static void cb_save_button(Fl_Button*, void*);
public:
  Fl_Button *new_button;
private:
  inline void cb_new_button_i(Fl_Button*, void*);
  static void cb_new_button(Fl_Button*, void*);
public:
  Fl_Button *undo_button;
private:
  inline void cb_undo_button_i(Fl_Button*, void*);
  static void cb_undo_button(Fl_Button*, void*);
public:
  Fl_Button *find_button;
private:
  inline void cb_find_button_i(Fl_Button*, void*);
  static void cb_find_button(Fl_Button*, void*);
public:
  Fl_Button *replace_button;
private:
  inline void cb_replace_button_i(Fl_Button*, void*);
  static void cb_replace_button(Fl_Button*, void*);
public:
  Fl_Button *cp_button;
private:
  inline void cb_cp_button_i(Fl_Button*, void*);
  static void cb_cp_button(Fl_Button*, void*);
public:
  Fl_Button *p_button;
private:
  inline void cb_p_button_i(Fl_Button*, void*);
  static void cb_p_button(Fl_Button*, void*);
public:
  Fl_Button *settings_button;
private:
  inline void cb_settings_button_i(Fl_Button*, void*);
  static void cb_settings_button(Fl_Button*, void*);
public:
  Fl_Button *cut_button;
private:
  inline void cb_cut_button_i(Fl_Button*, void*);
  static void cb_cut_button(Fl_Button*, void*);
public:
  Fl_Tabs *tabs;
private:
  inline void cb_tabs_i(Fl_Tabs*, void*);
  static void cb_tabs(Fl_Tabs*, void*);
public:
  Fl_Double_Window* pref_window();
  Fl_Double_Window *pref_win;
  Fl_Tabs *pref_tabs;
  Fl_Group *gen;
  Fl_Browser *font_b;
private:
  inline void cb_font_b_i(Fl_Browser*, void*);
  static void cb_font_b(Fl_Browser*, void*);
public:
  Fl_Output *font_show;
  Fl_Value_Output *font_save;
  Fl_Check_Button *tool_color;
private:
  inline void cb_tool_color_i(Fl_Check_Button*, void*);
  static void cb_tool_color(Fl_Check_Button*, void*);
public:
  Fl_Button *tExt;
private:
  inline void cb_tExt_i(Fl_Button*, void*);
  static void cb_tExt(Fl_Button*, void*);
public:
  Fl_Slider *f_s;
private:
  inline void cb_f_s_i(Fl_Slider*, void*);
  static void cb_f_s(Fl_Slider*, void*);
public:
  Fl_Value_Input *fsout;
private:
  inline void cb_fsout_i(Fl_Value_Input*, void*);
  static void cb_fsout(Fl_Value_Input*, void*);
public:
  Fl_Slider *l_s;
private:
  inline void cb_l_s_i(Fl_Slider*, void*);
  static void cb_l_s(Fl_Slider*, void*);
public:
  Fl_Value_Input *lsout;
private:
  inline void cb_lsout_i(Fl_Value_Input*, void*);
  static void cb_lsout(Fl_Value_Input*, void*);
public:
  Fl_Button *bg;
private:
  inline void cb_bg_i(Fl_Button*, void*);
  static void cb_bg(Fl_Button*, void*);
public:
  Fl_Group *syntax;
  Fl_Button *cm;
private:
  inline void cb_cm_i(Fl_Button*, void*);
  static void cb_cm(Fl_Button*, void*);
public:
  Fl_Button *str;
private:
  inline void cb_str_i(Fl_Button*, void*);
  static void cb_str(Fl_Button*, void*);
public:
  Fl_Button *symbols;
private:
  inline void cb_symbols_i(Fl_Button*, void*);
  static void cb_symbols(Fl_Button*, void*);
public:
  Fl_Button *typezz;
private:
  inline void cb_typezz_i(Fl_Button*, void*);
  static void cb_typezz(Fl_Button*, void*);
public:
  Fl_Button *keywordz;
private:
  inline void cb_keywordz_i(Fl_Button*, void*);
  static void cb_keywordz(Fl_Button*, void*);
public:
  Fl_Button *numbers;
private:
  inline void cb_numbers_i(Fl_Button*, void*);
  static void cb_numbers(Fl_Button*, void*);
public:
  Fl_Menu_Button *theme_button;
  Fl_Check_Button *plain_text;
  Fl_Button *directives;
private:
  inline void cb_directives_i(Fl_Button*, void*);
  static void cb_directives(Fl_Button*, void*);
public:
  Fl_Button *special;
private:
  inline void cb_special_i(Fl_Button*, void*);
  static void cb_special(Fl_Button*, void*);
public:
  Fl_Button *broken;
private:
  inline void cb_broken_i(Fl_Button*, void*);
  static void cb_broken(Fl_Button*, void*);
  inline void cb_Cancel_i(Fl_Button*, void*);
  static void cb_Cancel(Fl_Button*, void*);
  inline void cb_SAVE_i(Fl_Button*, void*);
  static void cb_SAVE(Fl_Button*, void*);
public:
  void add_tab(bool LOAD=true, bool NEW = true);
  int ask(std::string MSG, std::string yes="Yes", std::string no="No", std::string other="");
  static void ask_cb(Fl_Widget *o, long val);
  void button_style(int style=0);
  void change_theme(unsigned int FG,unsigned int BG, unsigned int selection, int font, int size, int line);
  int check_save();
  unsigned int choose_a_color(Fl_Widget *o);
  static void choose_doc(Fl_Widget* o, void* v);
  void close_tab();
  void colorize_syntax_buttons();
  void copy_cb();
  Fl_Syntax_Text_Editor * current_editor();
  void cut_cb();
  void default_theme();
  void delete_cb();
  void dnd_file(const char* items, bool NEW=true);
  std::vector<std::string> dnd_vec(std::string in);
  void find_cb();
  void find2_cb();
  void font_populate(Fl_Browser *o);
  std::string get_filename();
  void get_preferences();
  void get_theme_from_config(std::string theme);
  void goto_cb();
  void goto_line(int pos);
protected:
  static int handle(int event, Fl_Window *o);
public:
  static void handle_menu(Fl_Widget *w, void *v);
  std::string input(std::string MSG, std::string text, std::string ok="OK", std::string cancel="Cancel");
  void insert_cb();
  void load_file(std::string newfile, int ipos,bool NEW=true);
  void make_icon(Fl_Window *o);
  void none_theme();
  void make_theme_menu();
  void new_cb();
  void open_cb();
  void open_file(bool NEW=true);
  void paste_cb();
  bool pick_tab(std::string file);
  std::string prefline(std::string LINE,unsigned int COLOR);
  void print_cb();
  void quit_cb();
  void replace_cb();
  void replace2_cb();
  void replall_cb();
  void replace_start();
  void resize(Fl_Widget* o);
  void refresh_all();
  void save_cb(void);
  void saveas_cb(void);
  bool save_preferences();
  void save_file(std::string newfile);
  void set_title(Fl_Widget* g);
  void show_line_numbers(int width=0);
  static void theme_menu_cb(Fl_Widget* o, void* v);
  void undo_cb();
  void wordwrap();
};
std::vector<std::string> comma_line(std::string lang,std::string field);
unsigned int convert(std::string num, int default_value=0);
std::string get(std::string header, std::string line);
std::string get_syntax_file();
std::vector<std::string> get_syntax_headers();
std::string get_theme_file();
std::string get_type(std::string fname);
std::vector<std::string> get_themes();
int get_theme(std::string theme, std::string item, int default_value=0);
bool is_space(const char x);
std::vector <std::string> keywords(std::string header);
int main(int argc, char **argv);
std::vector<std::string> make_vec(std::string string_to_become_vector,std::string delimiter=" ");
void trace(std::string MSG, int n = 0);
bool test_file(std::string file);
std::vector <std::string> types(std::string header);
#endif
