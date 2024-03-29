// generated by Fast Light User Interface Designer (fluid) version 1.0304

#include <libintl.h>
#include "flrun.h"

void UI::cb_run_input_i(Fl_Input*, void*) {
  const char* tmp =run_input->value();
if(tmp==NULL)
  return;
run(tmp);
exit(0);
}
void UI::cb_run_input(Fl_Input* o, void* v) {
  ((UI*)(o->parent()->user_data()))->cb_run_input_i(o,v);
}

void UI::cb_OK_i(Fl_Button*, void*) {
  const char* tmp =run_input->value();
if(tmp==NULL)
  return;
run(tmp);
exit(0);
}
void UI::cb_OK(Fl_Button* o, void* v) {
  ((UI*)(o->parent()->user_data()))->cb_OK_i(o,v);
}

Fl_Double_Window* UI::make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(290, 35, gettext("Run"));
    w = o; if (w) {/* empty */}
    o->user_data((void*)(this));
    { run_input = new Fl_Input(35, 5, 160, 25, gettext("Run"));
      run_input->box(FL_FLAT_BOX);
      run_input->selection_color(FL_DARK_RED);
      run_input->callback((Fl_Callback*)cb_run_input);
      run_input->when(FL_WHEN_ENTER_KEY);
    } // Fl_Input* run_input
    { Fl_Button* o = new Fl_Button(200, 5, 70, 25, gettext("OK"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)62);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_OK);
    } // Fl_Button* o
    o->end();
  } // Fl_Double_Window* o
  return w;
}

int main(int argc, char *argv[]) {
  SingletonProcess singleton(6789);
  if (!singleton())
  {
    return 1;
  }
  std::string command;
  UI *ui = new UI();
  ui->make_window()->show();
  return Fl::run();
}

int usage(char* name) {
  std::cout<<name<<std::endl<<
  "USAGE:"<<std::endl<<
  "No Options"<<std::endl;
  return 0;
}
