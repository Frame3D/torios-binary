#include <FL/Fl_Pixmap.H>
#include "xpm/system-shutdown.xpm"
#include "xpm/system-restart.xpm"
#include "xpm/system-logout.xpm"
#include "xpm/system-hibernate.xpm"
#include "xpm/system-suspend.xpm"

#include "xpm/close.xpm"
#include "xpm/cut.xpm"
#include "xpm/color-cut.xpm"
#include "xpm/color-copy.xpm"
#include "xpm/copy.xpm"
#include "xpm/color-print.xpm"
#include "xpm/print.xpm"
#include "xpm/paste.xpm"
#include "xpm/color-paste.xpm"
#include "xpm/new.xpm"
#include "xpm/color-new.xpm"
#include "xpm/open.xpm"
#include "xpm/color-open.xpm"
#include "xpm/save.xpm"
#include "xpm/color-save.xpm"
#include "xpm/search.xpm"
#include "xpm/color-search.xpm"
#include "xpm/replace.xpm"
#include "xpm/color-replace.xpm"
#include "xpm/zoom-in.xpm"
#include "xpm/color-zoom-in.xpm"
#include "xpm/zoom-out.xpm"
#include "xpm/color-zoom-out.xpm"
#include "xpm/undo.xpm"
#include "xpm/color-undo.xpm"
#include "xpm/lock.xpm"
#include "xpm/settings.xpm"

//individual program Icons

//Text editor
#ifdef flpad_h
#include "xpm/flpad.xpm"
#endif

//Image viewer
#ifdef flimage_h
#include "xpm/flimage.xpm"
#endif

//Calculator
#ifdef SciCalc_h
#include "xpm/flcalc.xpm"
#endif

//Calendar
#ifdef flcalendar_h
#include "xpm/flcalendar.xpm"
#endif

//Same for color or BW
static Fl_Pixmap close_image(close_xpm);
static Fl_Pixmap settings_image(settings_xpm);


//BW
static Fl_Pixmap cut_image(cut_xpm);
static Fl_Pixmap paste_image(paste_xpm);
static Fl_Pixmap copy_image(copy_xpm);
static Fl_Pixmap new_image(new_xpm);
static Fl_Pixmap search_image(search_xpm);
static Fl_Pixmap save_image(save_xpm);
static Fl_Pixmap open_image(open_xpm);
static Fl_Pixmap undo_image(undo_xpm);
static Fl_Pixmap replace_image(replace_xpm);
static Fl_Pixmap zoom_in(zoom_in_xpm);
static Fl_Pixmap zoom_out(zoom_out_xpm);
static Fl_Pixmap lock_image(lock_xpm);
static Fl_Pixmap print_image(print_xpm);

//COLOR
static Fl_Pixmap color_zoom_out(color_zoom_out_xpm);
static Fl_Pixmap color_zoom_in(color_zoom_in_xpm);
static Fl_Pixmap color_cut_image(color_cut_xpm);
static Fl_Pixmap color_paste_image(color_paste_xpm);
static Fl_Pixmap color_copy_image(color_copy_xpm);
static Fl_Pixmap color_new_image(color_new_xpm);
static Fl_Pixmap color_search_image(color_search_xpm);
static Fl_Pixmap color_save_image(color_save_xpm);
static Fl_Pixmap color_open_image(color_open_xpm);
static Fl_Pixmap color_undo_image(color_undo_xpm);
static Fl_Pixmap color_replace_image(color_replace_xpm);
static Fl_Pixmap color_print_image(color_print_xpm);

// Power Management
static Fl_Pixmap shutdown_icon(system_shutdown_xpm);
static Fl_Pixmap restart_icon(system_restart_xpm);
static Fl_Pixmap suspend_icon(system_suspend_xpm);
static Fl_Pixmap hibernate_icon(system_hibernate_xpm);
static Fl_Pixmap logout_icon(system_logout_xpm);
