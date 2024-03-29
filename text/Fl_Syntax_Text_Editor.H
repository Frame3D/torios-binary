// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef Fl_Syntax_Highlighter_H
#define Fl_Syntax_Highlighter_H
#include <FL/Fl.H>
#include <X11/Xlib.h>
// copyright 2018 Israel Dahl
// GPL 3
// created from the FLTK tutorial using FLUID to design the UI
// created as part of the ToriOS project
#include "lexertk.hpp"
#include "../include/functions.h"
#include "../include/Fl_Functions.h"
#include <algorithm>
#include <sstream>
#include <iterator>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Printer.H>
#include <FL/Fl_Progress.H>
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
#include <sys/inotify.h>
#include <unistd.h>

class Fl_Syntax_Text_Editor : public Fl_Text_Editor
{
public:
  //This handles setting the syntax type
  void (*set_type)(Fl_Syntax_Text_Editor* e, std::string s);
  static void set_type_dummy(Fl_Syntax_Text_Editor* e, std::string s){}
  //this is the find callback
  void (*find_cb)(Fl_Syntax_Text_Editor* e);
  static void dummy_find_cb(Fl_Syntax_Text_Editor* e) {e->search_cb(0,0,"");}
  //this handles drag and drop functions
  void (*dnd_handle)(const char* t);
  static void dnd_handle_dummy(const char* t){}

protected:
  Fl_Menu_ *_menu;
  static void handle_menu(Fl_Widget* w , void *v)
  {
      if(!w || !v)
      {
          return;
      }
      Fl_Syntax_Text_Editor* T = (Fl_Syntax_Text_Editor*)w;

      if(T==NULL)
      {
          return;
      }

      switch(static_cast<int>(reinterpret_cast<long>(v)))
      {
          case 1: //COPY
              Fl_Text_Editor::kf_copy(0,T);
              break;
          case 2:  //CUT
              Fl_Text_Editor::kf_cut(0,T);
              break;
          case 3:  //FIND
              T->find_cb(T);
              break;
          case 4: //PASTE
              Fl_Text_Editor::kf_paste(0,T);
              break;
          case 5: //UNDO
              Fl_Text_Editor::kf_undo(0,T);
              break;
      }
}

  void make_popup(Fl_Widget *o)
  {
      //Fl_Syntax_Text_Editor
      Fl_Menu_Item rclick_menu[] = {
        { "Copy",  0, handle_menu, (void*)1 },
        { "Cut",  0, handle_menu, (void*)2 },
        { "Find",  0, handle_menu, (void*)3 },
        { "Paste",  0, handle_menu, (void*)4 },
        { "Undo",  0, handle_menu, (void*)5 },
        { 0 }
      };
      if(_menu == NULL)
        return;
      const Fl_Menu_Item *m = rclick_menu->popup(Fl::event_x(), Fl::event_y(), 0, 0, _menu);
      if ( m )
      {
          m->do_callback(o, m->user_data());
      }
      return;
  }
  int handle(int event)
  {
      switch(event)
      {
          case FL_PUSH:
          case FL_RELEASE:
              if(Fl::event_button() == FL_RIGHT_MOUSE)
              {
                  if(Fl::event_clicks())
                  {
                      break;
                  }
                  make_popup(this);
                  return 1;
              }
              break;
          case FL_DND_DRAG:
          case FL_DND_LEAVE:
          case FL_DND_RELEASE:
              RELEASE = true;
              break;
          case FL_PASTE:
              if(RELEASE)
              {
                  RELEASE   = false;
                  dnd_handle(Fl::event_text()); //TODO
                  return 1;
              }
              break;
      }
      //    check_inotify();
  
      return Fl_Text_Editor::handle(event);
  }

public:
  lexertk::generator *generator; 
  Fl_Printer *printer;
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
  int INDENT_NEW_LINES;
  int WORD_WRAP;
  int TAB_DISTANCE;
  int inotify_fd; 
  int inotify_wd;
  bool SPACES; 
  bool WRAPPED; 
  bool IGNORE_SYNTAX_CASE; 
  bool RELEASE, DND_START; 
  Fl_Text_Display::Style_Table_Entry styletable[10]; 
  Fl_Text_Buffer * stylebuffer; 
  Fl_Text_Buffer * textbuffer;
  Fl_Progress* progress;
  std::string filename; 
  std::string search; 
  int is_changed; 
  int loading;

  std::vector<std::string> KEYWORDS, TYPES; 
  lexertk::helper::bracket_checker bracket_checker;
  lexertk::helper::symbol_replacer symbol_replacer;
  std::string STYLE_HEADER;
  
  void trace(std::string msg){std::cout<<msg<<std::endl;}
  
  int search_cb (int match_case=0, int backward=1 , std::string term="")
  {
      int pos = insert_position();

      if(search.compare("")==0)
      {
          char * tmp = textbuffer->selection_text();
          if(tmp != NULL)
          {
            search = tmp;
          }
      }

      if(term.compare("")==0)
      {
          term = search;
      }

      int found = 0;
  
      if(backward)
      {
          int init = textbuffer->line_start(pos);
          init--;
          textbuffer->line_start(init);
          found = textbuffer->search_backward(init, term.c_str(), &pos, match_case);
      }
      else
      {
          found = textbuffer->search_forward(pos, term.c_str(), &pos, match_case);
      }
  
      if (found)
      {
    // Found a match; select and update the position...
          textbuffer->select(pos, (pos + term.length()) );
          search = textbuffer->selection_text();
          insert_position(pos + term.length());
          show_insert_position();
          return 1;
      }
      else
      {
          if(textbuffer->selected())
          {
              return 0;
          }
          else
          {
              return -1;
          }
      }
  }
  void set_syntax_colors(
                          unsigned int foreground_text,
                          unsigned int background_text,
                          unsigned int selection_text,
                          unsigned int comment_text,
                          unsigned int string_text,
                          unsigned int directive_text,
                          unsigned int number_text,
                          unsigned int keyword_text,
                          unsigned int type_text,
                          unsigned int symbols_text,
                          unsigned int special_text,
                          unsigned int broken_text
                        )
  {
      FOREGROUND_TEXT = foreground_text;
      BACKGROUND_TEXT = background_text;
      SELECTION_TEXT = selection_text;
      COMMENT_TEXT = comment_text;
      STRING_TEXT = string_text;
      DIRECTIVE_TEXT = directive_text;
      NUMBER_TEXT = number_text;
      KEYWORD_TEXT = keyword_text;
      TYPE_TEXT = type_text;
      SYMBOLS_TEXT = symbols_text;
      SPECIAL_TEXT = special_text;
      BROKEN_TEXT = broken_text;
  }

  void default_style(){set_syntax_colors(0,255,0,0,0,0,0,0,0,0,0,0);}


  void set_menu(Fl_Menu_ *m)
  {
      _menu=m;
  }

  void init_inotify(std::string file)
  {
      inotify_fd = inotify_init();
      inotify_wd = inotify_add_watch (inotify_fd, file.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
  
      if ( inotify_wd < 0 )
      {
          perror("inotify_add_watch failed");
      }
  }

  int rm_inotify(){return inotify_rm_watch (inotify_fd, inotify_wd);}

  bool check_inotify()
  {
     if(filename.compare("")==0)
    return false;
  //Took this directly from an old linux journal article
  struct timeval time;
  fd_set rfds;
  int ret;
  
  /* timeout after five seconds */
  time.tv_sec = 5;
  time.tv_usec = 0;
  
  /* zero-out the fd_set */
  FD_ZERO (&rfds);
  
  /*
   * add the inotify fd to the fd_set -- of course,
   * your application will probably want to add
   * other file descriptors here, too
   */
  FD_SET (inotify_fd, &rfds);
  
  std::string File_was_modified = gettext(" was modified,\ndo you want to reload it?");
  
  ret = select (inotify_fd + 1, &rfds, NULL, NULL, &time);
  
  if( (ret !=0) && (FD_ISSET (inotify_fd, &rfds)) )
  {
    /* TODO ask?????
    if(ask(filename + File_was_modified)==1)
    {
      //they want to reload it
      rm_inotify();
      textbuffer->loadfile(filename.c_str());
      init_inotify(filename.c_str());
      modify_cb();
    }
    */
    return true;
  }
  return false; 
  }

  void word_wrap()
  {
     if(WRAPPED)
     {
         WRAPPED=false;
         wrap_mode(Fl_Text_Display::WRAP_NONE, 0);
         WORD_WRAP=0;
     }
     else
     {
         WRAPPED=true;
         wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
         WORD_WRAP=1;
     } 
  }

  int tab_distance(){return textbuffer->tab_distance();}

  void tab_distance(int dist)
  {
      textbuffer->tab_distance(dist);
      stylebuffer->tab_distance(dist);
  }

  std::string style_line(std::string thisLine)
  {
      if(!generator->process(thisLine))
      {
          std::string ret;
          for(unsigned int i = 0; i < thisLine.length(); i++)
          {
              char tmp = thisLine[i];
              if(
                 (tmp != '\n') ||
                 (tmp != '\t') ||
                 (tmp != '\r') ||
                 (tmp != ' ')
                )
              {
                  ret += 'A';
              }
              else
              {
                  ret += tmp;
              }
      
          }
          return ret;
      }
      else
      {
          std::string line = lexertk::helper::style_line(generator);
          if(line.compare("")==0)
          {
              line = "\n";
          }
          return line;
      }
  
  // this should never happen....
      return "A";
  }

  void modify_cb(int pos=0, int nInserted=0, int nDeleted=0, int unused=0, const char * nada=NULL)
  {
      //if it is a selection change just return
      if(stylebuffer->selected() != 0)
      {
          stylebuffer->unselect();
          return;
      }
      
      std::string thisLine;
  
      if ( (HIGHLIGHT_PLAIN==0) && (STYLE_HEADER.compare("")==0) )
      {
          char *style = new char[textbuffer->length() + 1];
          memset(style, 'A', textbuffer->length());
          style[textbuffer->length()] = '\0';
          stylebuffer->text(style);
      }
      else
      {
          char* buf = this->textbuffer->text();
  
          if(buf == NULL)
          {
              return;
          }
  
          std::string out(buf);
          std::string res = style_line(out);
          char* RES = const_cast <char*> (res.c_str());
  
          if (RES == NULL)
          {
              return;
          }
  
          stylebuffer->text(RES);
      }
  
      redisplay_range(0,textbuffer->length());
  }

  int line_count(){return count_lines(0,length(), false);}

  int pages()
  {
      wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
      WRAPPED = !WRAPPED;
      int f = textsize();
      int l = line_count();
      int tot = f * l;
      word_wrap();
  
      if ( tot < 1)
      {
          return 0;
      }

      int w, h;
      printer->printable_rect(&w, &h);
  
  
      if (tot < h)
      {
          return 1;
      }
  
      int total = tot / h;
      std::cout<<"total pages:"<<total<<std::endl;
      return total;
  }

  int lines_per_page() { return (line_count() / pages()); }

  int size()
  {
      const char* txt = textbuffer->text();
  
      if(txt == NULL)
      {
          return 0;
      }
  
      return strlen(txt);
  }

  std::string count_spaces()
  {
      int pos = insert_position();
      std::string spaces;
      int Pos = textbuffer->line_start(pos);
      if(Pos == pos)
          return "";
  
      if(SPACES)
      {
          int start = textbuffer->line_start(pos);
          int end   = textbuffer->line_end(pos);
          int init = 0;
          for(int i = start; i < end; i++)
          {
              char A = textbuffer->char_at(i);
              if ( (' ' == A) || ( '\t' == A) )
              {
                  spaces+=A;
                  init++;
              }
              else
                  break;
          }
      }
      return spaces;
  }

  static void kill_selection(Fl_Text_Editor* e)
  {
      if (e->buffer()->selected())
      {
          e->insert_position(e->buffer()->primary_selection()->start());
          e->buffer()->remove_selection();
      }
  }

  static int enter_kf(int, Fl_Text_Editor *e)
  {
      //Basically I copied the original code from the text editor source
      kill_selection(e);
  
  //I changed this to my widget
      Fl_Syntax_Text_Editor* E = (Fl_Syntax_Text_Editor*)e;
  
  //I use the space counter function
      std::string SPACES = E->count_spaces();
  // instead of just adding a newline like in the original, I also add the spaces
      std::string t  = "\n";
                  t += SPACES;
  //put it in
      e->insert(t.c_str());
  //put the cursor right there
      e->show_insert_position();
  //make it changed
      e->set_changed();
  //do the callback if needed
      if (e->when()&FL_WHEN_CHANGED)
      {
          e->do_callback();
      }
  //return 'it worked' this is like the boolean 'true' here
      return 1;
  }

  void get_styletable(Fl_Text_Display::Style_Table_Entry &styles,int which)
  {
     // this function does all the repetative styletable work,
     // and keeps it organized in one place
  
     //get the current font
     int font = FONT_TEXT;
  //usually (unless they chose a bold/italic font) bold is next one up
     int bold = font + 1;
  // usually (unless they chose a bold/italic font) italic is next one up
     int ital = bold + 1;
  
     switch(which)
     {
         case 0:
          // the format:  COLOR        font   NORMAL SIZE
            styles={ FOREGROUND_TEXT, font, FL_NORMAL_SIZE }; // A - Plain
            break;
         case 1:
            styles={ COMMENT_TEXT, ital, FL_NORMAL_SIZE }; // B - Line comments
            break;
         case 2:
            styles={ DIRECTIVE_TEXT, ital, FL_NORMAL_SIZE }; // C -Directives
            break;
         case 3:
            styles={ STRING_TEXT, font, FL_NORMAL_SIZE }; // D - Strings
            break;
         case 4:
            styles={ SYMBOLS_TEXT, font, FL_NORMAL_SIZE }; // E - Symbols
            break;
         case 5:
            styles={ TYPE_TEXT, bold, FL_NORMAL_SIZE }; // F - Types
            break;
         case 6:
            styles={ KEYWORD_TEXT, bold, FL_NORMAL_SIZE }; // G - Keywords
            break;
         case 7:
            styles={ NUMBER_TEXT, font, FL_NORMAL_SIZE }; // H - numbers
            break;
         case 8:
            styles={ SPECIAL_TEXT, font, FL_NORMAL_SIZE }; // I - special
            break;
         case 9:
            styles={ BROKEN_TEXT, font, FL_NORMAL_SIZE }; // J - Broken :(
            break;
     }
     styletable[which] = styles; //  set 
  }

  void use_spaces()
  {
      remove_key_binding(FL_Enter,FL_TEXT_EDITOR_ANY_STATE);
  
  // this will either use default enter function
  // OR it will use the function tat adds the right amount of spaces for indention
      if(SPACES)
      {
        //use my function
          add_key_binding(FL_Enter,FL_TEXT_EDITOR_ANY_STATE,enter_kf);
      }
      else
      {
        //use default function
          add_key_binding(FL_Enter,FL_TEXT_EDITOR_ANY_STATE,kf_enter);
      }
  }

  void update_styletable()
  {
      Fl_Text_Display::Style_Table_Entry A; //  Plain
      get_styletable(A,0);
  
      Fl_Text_Display::Style_Table_Entry B; // Line comments
      get_styletable(B,1);
  
      Fl_Text_Display::Style_Table_Entry C; // Block comments
      get_styletable(C,2);
  
      Fl_Text_Display::Style_Table_Entry D; // Strings
      get_styletable(D,3);
  
      Fl_Text_Display::Style_Table_Entry E; // Directives
      get_styletable(E,4);
  
      Fl_Text_Display::Style_Table_Entry F; // Types
      get_styletable(F,5);
  
      Fl_Text_Display::Style_Table_Entry G;  // Keywords
      get_styletable(G,6);
  
      Fl_Text_Display::Style_Table_Entry H; // Numbers
      get_styletable(H,7);
  
      Fl_Text_Display::Style_Table_Entry I; // Special
      get_styletable(I,8);
  
      Fl_Text_Display::Style_Table_Entry J; // Broken
      get_styletable(J,9);
  
      use_spaces();
  }

  void init_highlight()
  {
      update_styletable();
  
      highlight_data(stylebuffer, styletable, sizeof(styletable) / sizeof(styletable[0]), 'A', style_unfinished_cb, 0);
      textbuffer->add_modify_callback(style_update, (void*) this);
  }

  void theme_editor(
                     unsigned int FG,
                     unsigned int BG,
                     unsigned int selection,
                     int font,
                     int size,
                     int linenum,
                     unsigned int comment_text,
                     unsigned int string_text,
                     unsigned int directive_text,
                     unsigned int number_text,
                     unsigned int keyword_text,
                     unsigned int type_text,
                     unsigned int symbols_text,
                     unsigned int special_text,
                     unsigned int broken_text
                   )
  {
      set_syntax_colors(FG,BG,selection,comment_text,string_text,directive_text,number_text,keyword_text,type_text,symbols_text,special_text,broken_text);
      textcolor(FG);
      cursor_color(FG);
      color(BG);
      textfont(font);
      textsize(size);
      selection_color(selection);
      linenumber_width(linenum);
      linenumber_size(size);
  
  ///renew syntax highlighting
      update_styletable();
  //make the syntax highlighter colors
      modify_cb();
  //make the tab distance the correct one
      tab_distance(TAB_DISTANCE);
  //redo the syntax highlighting to make sure tabs are correct
      modify_cb();
  }

  Fl_Syntax_Text_Editor(int x, int y, int w, int h, const char* label = 0) : Fl_Text_Editor(x,y,w,h,label)
  {
     IGNORE_SYNTAX_CASE = false;
     SPACES             = false;
     RELEASE            = false;
     DND_START          = false;
     WRAPPED            = false;
     is_changed         = 0;
     loading            = 0;
     filename           = "";
     dnd_handle         = dnd_handle_dummy; //prevent crashing
     set_type           = set_type_dummy; //prevent crashing
     find_cb            = dummy_find_cb; //prevent crashing
     _menu              = NULL;
     progress           = NULL;

     default_style(); //make colors
  
  //the buffer to hold just the file's text
     textbuffer         = new Fl_Text_Buffer();
     resize(x,y,w,h);
  //set textbuffer to be the buffer in this widget
     buffer(textbuffer);
  
  // create a basic style text
     char *style = new char[textbuffer->length() + 1];
  //set it to plain .a.k.a. 'A'
     memset(style, 'A', textbuffer->length());
  
  // this is the buffer for the syntax highlighting
     stylebuffer = new Fl_Text_Buffer(textbuffer->length());
     style[textbuffer->length()] = '\0';
  //get the actual syntax highlighter setup
     init_highlight();
  //set the highlighter text in the style buffer
     stylebuffer->text(style);
  
  //don't need these anymore
     delete[] style;
  
  //make it flat so it looks nicer
     box(FL_FLAT_BOX);
  
  //make this editor have the right font, line numbers, and colors
     theme_editor(
                  FOREGROUND_TEXT,
                  BACKGROUND_TEXT,
                  SELECTION_TEXT,
                  FONT_TEXT,
                  SIZE_TEXT,
                  LINE_NUMBERS,
                  COMMENT_TEXT,
                  STRING_TEXT,
                  DIRECTIVE_TEXT,
                  NUMBER_TEXT,
                  KEYWORD_TEXT,
                  TYPE_TEXT,
                  SYMBOLS_TEXT,
                  SPECIAL_TEXT,
                  BROKEN_TEXT
                 );

  //whenever the buffer is modified run this function
       textbuffer->add_modify_callback(changed_cb,(void *)this);
  //setup the printer for this widget
       printer = new Fl_Printer();
  //make it so typing happens here (instead of the tab or something un-helpful)
       Fl::focus(this);
}

  ~Fl_Syntax_Text_Editor()
  {
       buffer(0);
       textbuffer->remove_modify_callback(style_update, this);
       textbuffer->remove_modify_callback(changed_cb, this);
  
       delete printer;
       delete textbuffer;
       delete stylebuffer;
  
       if(rm_inotify())
       {
         //trace("problem removing inotify watch");
       }
 
  }

  static void changed_cb(int, int nInserted, int nDeleted, int, const char*, void *v)
  {
      Fl_Syntax_Text_Editor * o = (Fl_Syntax_Text_Editor *)v;
      std::string f = o->filename;
      o->is_changed = 0;
  
      if ((nInserted || nDeleted) && !o->loading)
      {
          o->is_changed = 1;//o->set_changed();
      }
  
      //((UI *)(o->parent()->user_data()))->set_title(o->parent());
  }

  std::string file_string()
  {
      // turn a file into a string
  
      //no file sent in... return emptyness
      if( (filename.compare("")==0) || (!test_file(filename)) )
      {
           return "";
      }
  
      //make our input file stream, and put the file into it
      std::ifstream t(filename);
      //make our return string
      std::string str;
  
      //set position to end
      t.seekg(0, std::ios::end);
      //make the string a nice size
      str.reserve(t.tellg());
      //set position back to start
      t.seekg(0, std::ios::beg);
      //now use the iterators to assign the entire file to the string
      str.assign((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());
      //voila ca cest tres bein!
      return str;
  }



  int length(){return textbuffer->length();}

  static void style_update(int pos=0, int nInserted=0, int nDeleted=0, int unused=0, const char * nada=NULL, void *cbArg = NULL)
  {
      Fl_Syntax_Text_Editor * ED = (Fl_Syntax_Text_Editor *)cbArg;
      if(ED==NULL)
      {
          return;
      }
      ED->modify_cb(pos, nInserted, nDeleted, unused, nada);
  }

  static void style_unfinished_cb(int, void*){}


  Fl_Double_Window* progress_window()
  {
    Fl_Double_Window* w;
    {
        Fl_Double_Window* o = new Fl_Double_Window(440, 140, gettext("Printer Progress"));
        w = o; if (w) {/* empty */}
        o->user_data((void*)(this));
        {
            progress = new Fl_Progress(40, 80, 355, 30);
            progress->box(FL_FLAT_BOX);
            progress->color((Fl_Color)38);
            progress->selection_color((Fl_Color)71);
        } // Fl_Progress* progress
        o->end();
    } // Fl_Double_Window* o
    return w;
  }

  std::string page(int num)
  {
     int lines = lines_per_page();
     int start = lines * num;
  
     int end = start + lines;
  
     const char* text = textbuffer->text_range(start, end);
     std::cout<<"page:"<<num<<" start:"<<start<<" text:"<<text<<std::endl;
     if(text == NULL)
     {
         return "";
     }
  
     std::string t = text;
     return t; 
  }
  void print_page(int w, int h, int font, int size, int page_num)
  {
      int x = 0;
      int y = 0;
  
      printer->start_page();
  
      fl_color(FL_BLACK);
      fl_rect(x,y,w,h);
      fl_font(font, size);
      fl_draw( page(page_num).c_str(), x, y, w, h, FL_ALIGN_WRAP );
  
      printer->end_page();
  }

  void print_text()
  {
      int font            = textfont();
      int size            = textsize();
      int start, end;
      int w,h;
      printer->printable_rect(&w,&h);
      std::string labl = gettext("Printing Page #: ");
      if (printer->start_job(0, &start, &end) == 0)
      {
          if(end == start)
          {
              print_page(w, h, font, size, start);
              return;
          }
  //show progress
          start -= 1;
          int inc = 100 / (end/start);
          progress_window()->show();
          int p_val = 0;
          progress->value(p_val);
          std::cout<<"start:"<<start<<" end:"<<end<<std::endl;
          for (int i = start; i < end; i++)
          {
              std::cout<<"printing:"<<i<<std::endl;
              print_page(w, h, font, size, i);
              p_val += inc;
              std::string num = labl + convert(i);
              progress->value(p_val);
              progress->copy_label(num.c_str());
          }
  
          progress_window()->hide();
          std::cout<<"done"<<std::endl;
          printer->end_job();
      }
  }

  void refresh()
  {
      set_syntax();
      modify_cb(0,0,0,0,NULL);
      redisplay_range(0,textbuffer->length());
      redraw();
  }

  void set_syntax(){set_type(this,filename);}

};
#endif
