#ifndef Fl_Functions_h
#define Fl_Functions_h

#include <FL/fl_ask.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl.H>

#include "functions.h"

int ret_val; 

void font_populate(Fl_Browser *o)
{
  Fl_Font a;
  a = Fl::set_fonts("-*");
  std::string v;
  Fl_Font i;
  for (i = 1; i != a; ++i)
  {
    v = Fl::get_font_name(i,0);
    o->add(v.c_str());
  }
}

void alert(std::string msg="Encountered an Error")
{
    std::cerr << msg << std::endl;
    fl_alert("%s", msg.c_str());
}

void ask_cb(Fl_Widget *o, long val)
{
  ret_val = (int) val;
  o->parent()->hide();
}

int ask(std::string MSG, std::string yes="Yes", std::string no="No", std::string other="")
{
  int w = 500;
  int h = 90;
  Fl_Double_Window* ask_win = new Fl_Double_Window(w, h);
  
  Fl_Box* o = new Fl_Box(5, 5, 5, 5);
  o->copy_label(MSG.c_str());
  o->redraw();
  
  Fl_Button* o1 = new Fl_Button(170, 55, 65, 30, yes.c_str());
  o1->box(FL_FLAT_BOX);
  o1->color((Fl_Color)62);
  o1->labelcolor(FL_BACKGROUND2_COLOR);
  o1->callback(ask_cb,1);
  
  Fl_Button* o2 = new Fl_Button(100, 55, 65, 30, no.c_str());
  o2->box(FL_FLAT_BOX);
  o2->color((Fl_Color)80);
  o2->labelcolor(FL_BACKGROUND2_COLOR);
  o2->callback(ask_cb,0);
  
  if(other.compare("")!=0)
  {
    Fl_Button* o3 = new Fl_Button(30, 55, 65, 30, other.c_str());
    o3->box(FL_FLAT_BOX);
    o3->color((Fl_Color)94);
    o3->labelcolor(FL_BACKGROUND2_COLOR);
    o3->callback(ask_cb,2);
  }
  else
  {
    o1->position(5,o1->y());
    o2->position(10+o1->w(),o1->y());
    
  }
  
  ask_win->end();
  ask_win->show();
  
  o->measure_label(w,h);
  o->size(w+10,h);
  if(other.compare("")!=0)
  {
    if(w < ask_win->w())
    {
       w = ask_win->w() + 10;
    }
    else if (w > ask_win->w())
    {
      ask_win->size((w + 10), ask_win->h());
    }
    else
    {
      w += 10;
    }
    if(h<ask_win->h())
    {
      h=ask_win->h();
    }
    else if (h > ask_win->h())
    {
      ask_win->size(ask_win->w(),(h + 10));
    }

    else
      h +=10;
  }
  else
  {
    int W = o2->x()+o2->w()+5;
    if(w<W)
       w=W;
    else if (w < W +10)
      w=W+10;
    else
      w+=10;
    if(h<ask_win->h())
      h=ask_win->h();
    else
      h +=10;
  }
  
  ask_win->size(w,h);
  
  while (ask_win->shown()) Fl::wait();
  
  return ret_val;
}


void make_icon(Fl_Window *o, const char* const *pxmp)
{
  Fl_Pixmap f(pxmp);
  const Fl_Pixmap * flpad_xpm_icon = &f;
  const Fl_RGB_Image *img = new Fl_RGB_Image(flpad_xpm_icon,FL_GRAY);
  o->icon(img);
}


std::string file_chooser(std::string types="*", std::string where="", std::string label="Open File?")
{
  if(label.compare("")==0)
  {
    label = "Choose";
  }
  
  if(where.compare("")==0)
  {
    const char* home = getenv("HOME");
    if(home != NULL)
    {
      where = home;
    }
  }
  
  if(types.compare("")==0)
  {
    types = "*";
  }
  
  const char* f = where.c_str();
  const char* m = label.c_str();
  const char* p = types.c_str();
  
  Fl_Native_File_Chooser fnfc;
  fnfc.title(m);
  fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
  fnfc.options(Fl_Native_File_Chooser::PREVIEW);
  fnfc.filter(p);
  fnfc.directory(f); // default directory to use
  
  // Show native chooser
  switch ( fnfc.show() )
  {
    case -1: break; // ERROR
    case  1: break; // CANCEL
    default:
      const char *result = fnfc.filename();
  
      if(result != NULL)
      {
        std::string String = result;
        return String;
      }
      break; // FILE CHOSEN
  }
  
  return "";
}

std::string dir_chooser(std::string directory, std::string label)
{
  if(directory.compare("")==0)
  {
    const char* home = getenv("HOME");
    if(home != NULL)
    {
      directory = home;
    }
  }
  
  if(label.compare("")==0)
  {
    label = "Choose Directory";
  }
  
  Fl_Native_File_Chooser fnfc;
  fnfc.title(label.c_str());
  fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
  fnfc.directory(directory.c_str());
  
  std::string String;
  
  // Show native chooser
  switch ( fnfc.show() )
  {
    case -1: break; // ERROR
    case 1: break; // CANCEL
    default:
      const char *result =fnfc.filename();
      if(result!=NULL)
      {
        String = result;
      }
  }
  
  if(String.compare("")!=0)
  {
    std::string message  = "Save as ";
                message += String;
  
    int choice = fl_choice("Save ?","No","Yes","Cancel");
  
    if (choice!=1)
    {
      return "";
    }
  }
  
  return String;
}

unsigned int choose_a_color(Fl_Widget *o)
{
    uchar r;
    uchar g;
    uchar b;
    Fl::get_color((o->color()),r,g,b);
    int c;
    const char * label ="Choose a Color";
    c = fl_color_chooser(label,r,g,b,2);

    if(c != 1)
    {
        return o->color();
    }

    unsigned int C = fl_rgb_color(r,g,b);
    o->color(C);
    o->redraw();
    return o->color();
}

void under_mouse(Fl_Window *o)
{
    int x,y;
    Fl::get_mouse(x,y);
    o->position(x,y);
    o->redraw();
}

#endif