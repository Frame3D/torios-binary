#ifndef Fl_Input_Menu_H
#define Fl_Input_Menu_H

#include <Fl/Fl_Menu_Button.H>
#include <Fl/Fl_Group.H>
#include <vector>
#include <string>
#include <FL/fl_draw.H>
#include <FL/Fl_Input.H>

/* I changed the default input menu button to be like I want
   most of this is just ripped off from FLTK sources and modifed to do what I want
*/
class InputMenuButton : public Fl_Menu_Button
{
    public:
        InputMenuButton(int x,int y,int w,int h,const char*l=0):Fl_Menu_Button(x,y,w,h,l)
        {
            box(FL_FLAT_BOX);
        }
    private:
        void draw()
        {
            draw_box(FL_FLAT_BOX, color());
            fl_color(active_r() ? labelcolor() : fl_inactive(labelcolor()));
            int xc = x()+w()/2;
            int yc=y()+h()/2;
            fl_polygon(xc-5,yc-3,xc+5,yc-3,xc,yc+3);
            if (Fl::focus() == this) draw_focus();
        }


};

class Fl_Input_Menu : public Fl_Group
{

    private:
        bool m_menu_on_right; 
        int m_width; 
        Fl_Input* m_input; 
        InputMenuButton *m_menu; 

        static void _menu_cb(Fl_Widget*, void *data)
        {
            Fl_Input_Menu *o=(Fl_Input_Menu *)data;
            Fl_Widget_Tracker wp(o);
            const Fl_Menu_Item *item = o->menubutton()->mvalue();
            if (item && item->flags & (FL_SUBMENU|FL_SUBMENU_POINTER)) return;  // ignore submenus
            if (!strcmp(o->m_input->value(), o->m_menu->text()))
            {
                o->Fl_Widget::clear_changed();
                if (o->when() & FL_WHEN_NOT_CHANGED)
                    o->do_callback();
            }
            else
            {
                o->m_input->value(o->m_menu->text());
                o->m_input->set_changed();
                o->Fl_Widget::set_changed();
                if (o->when() && (FL_WHEN_CHANGED|FL_WHEN_RELEASE))
                    o->do_callback();
            }
  
            if (wp.deleted()) return;
  
            if (o->callback() != default_callback)
            {
                o->Fl_Widget::clear_changed();
                o->m_input->clear_changed();
            }
        }

        static void _input_cb(Fl_Widget*, void *data)
        {
              Fl_Input_Menu *o=(Fl_Input_Menu *)data;
              Fl_Widget_Tracker wp(o);
  
              if (o->m_input->changed())
              {
                  o->Fl_Widget::set_changed();
  
                  if (o->when() & (FL_WHEN_CHANGED|FL_WHEN_RELEASE))
                  {
                      o->do_callback();
                  }
              }
              else
              {
                  o->Fl_Widget::clear_changed();
  
                  if (o->when() & FL_WHEN_NOT_CHANGED)
                  {
                      o->do_callback();
                   }
              }
  
              if (wp.deleted())
              {
                  return;
              } 
              if (o->callback() != default_callback)
              {
                  o->Fl_Widget::clear_changed();
              }
        }

        inline int _InpSizeW(){return(w() - m_width);}

    public:
        Fl_Input_Menu(int x,int y,int w,int h,const char*l=0):Fl_Group(x,y,w,h,l)
        {
            Fl_Group::box(FL_NO_BOX);
            m_width = 20;
            align(FL_ALIGN_LEFT);

            m_menu_on_right = false;

            m_input = new Fl_Input       (x + m_width,   y, (w-m_width), h);
            m_menu  = new InputMenuButton(x,             y,    m_width,  h);

            m_input->box(FL_FLAT_BOX);
            m_input->selection_color(60);
            m_input->callback(_input_cb, (void*)this);
            m_menu->callback(_menu_cb, (void*)this);
            m_menu->box(FL_FLAT_BOX);
            m_menu->down_box(FL_FLAT_BOX);
            m_menu->color(23);
            m_menu->selection_color(60);
  
            end();
        }

        void add(const char* val){m_menu->add(val);}

        void add(std::string val){m_menu->add(val.c_str());}

        void add(std::vector<std::string> values)
        {
            for( std::vector<std::string>::iterator itr = values.begin();
                                                    itr!= values.end();
                                                  ++itr)
            {
                std::string val = *itr;
                m_menu->add(val.c_str());
            }
        }

        void clear(){ m_menu->clear();}

        void clear_changed()
        {
            m_input->clear_changed();
            Fl_Widget::clear_changed();
        }

        void resize(int X, int Y, int W, int H)
        {
            Fl_Group::resize(X,Y,W,H);
             m_width = 20;
             int input_w = W - m_width;
             if(m_menu_on_right)
             {
                 m_input->resize (  X,             Y, input_w, H);
                 m_menu->resize  ( (X + input_w),  Y, m_width, H);
             }
             else
             {
                 m_menu->resize  (  X,             Y, m_width, H);
                 m_input->resize ( (X + m_width),  Y, input_w, H);
             }
  /*
  button (x,             y,    m_width,  h);
  input  (x + m_width,   y, (w-m_width), h);
  */
        }

        void menuvalue(int val)
        {
          m_menu->value(val);
          m_input->value(m_menu->text(val));
        }


        void inputvalue(const char *val){m_input->value(val);}

        const char* inputvalue(){return(m_input->value());}

        const char* value(){return(inputvalue());}

        void value(int val){menuvalue(val);}

        void value(const char *val){m_input->value(val);}

        Fl_Menu_Button* menubutton(){return (m_menu);}

        Fl_Input* input(){return (m_input);}

        void flip()
        {
            m_menu_on_right=!m_menu_on_right;
            resize(x(),y(),w(),h());
        }

        void set_changed(){m_input->set_changed();}

        int size(){return m_menu->size();}

        bool empty(){return ((size() < 2) ? true : false);}
};

#endif