#include <FL/Fl_Pixmap.H>

static const char * close_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #940000",
"                ",
"                ",
"                ",
"  ....    ....  ",
"  .....  .....  ",
"   ..........   ",
"    ........    ",
"     ......     ",
"     ......     ",
"    ........    ",
"   ..........   ",
"  .....  .....  ",
"  ....    ....  ",
"                ",
"                ",
"                "};
static const char * cut_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"  ..        ..  ",
"  ...      ...  ",
"  ....    ....  ",
"  .....  .....  ",
"   ..........   ",
"    ........    ",
"     ......     ",
"     ......     ",
"    ........    ",
"  ............  ",
" ... .. ..  ... ",
" ... ..  .. ... ",
"  .....  .....  ",
"   ...    ...   ",
"                "};
static const char * color_cut_xpm[] = {
"16 16 3 1",
" 	c None",
".	c #e8e7e7",
"-	c #969595",
"                ",
"  ..        --  ",
"  ...      ---  ",
"  ....    ----  ",
"  .....  -----  ",
"   .....-----   ",
"    .....---    ",
"     .....-     ",
"     -.....     ",
"    ---.....    ",
"  ------......  ",
" --- -- ..  ... ",
" --- --  .. ... ",
"  -----  .....  ",
"   ---    ...   ",
"                "};
static const char * color_copy_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #000000",
"-	c #6f6969",
"@	c #FFFFFF",
"                ",
"  ----------    ",
"  ----------    ",
"  --@@@@@@@@@@  ",
"  --@@@@@@@@@@  ",
"  --@@......@@  ",
"  --@@@@@@@@@@  ",
"  --@@@....@@@  ",
"  --@@@@@@@@@@  ",
"  --@@......@@  ",
"  --@@@@@@@@@@  ",
"  --@@......@@  ",
"    @@@@@@@@@@  ",
"    @@@@@@@@@@  ",
"                ",
"                "};
static const char * copy_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"  ..........    ",
"  ..........    ",
"  ............  ",
"  ...        .  ",
"  ... ...... .  ",
"  ...        .  ",
"  ...  ....  .  ",
"  ...        .  ",
"  ... ...... .  ",
"  ...        .  ",
"  ... ...... .  ",
"    .        .  ",
"    ..........  ",
"                ",
"                "};
static const char * paste_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"     ......     ",
"   ..........   ",
"  .. ...... ..  ",
"  ..        ..  ",
"  .. ...... ..  ",
"  ..        ..  ",
"  ..  ....  ..  ",
"  ..        ..  ",
"  .. ...... ..  ",
"  ..        ..  ",
"  .. ...... ..  ",
"  ..        ..  ",
"  ............  ",
"  ............  ",
"                "};
static const char * color_paste_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #000000",
"-	c #e9b080",
"+	c #aaaaaa",
"@	c #FFFFFF",
"                ",
"     ++++++     ",
"    @++++++@    ",
"  --@++++++@--  ",
"  --@@@@@@@@--  ",
"  --@......@--  ",
"  --@@@@@@@@--  ",
"  --@@....@@--  ",
"  --@@@@@@@@--  ",
"  --@......@--  ",
"  --@@@@@@@@--  ",
"  --@......@--  ",
"  --@@@@@@@@--  ",
"  ------------  ",
"  ------------  ",
"                "};
static const char * new_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"  ............  ",
"  .          .  ",
"  .          .  ",
"  .          .  ",
"  .          .  ",
"  .        ...  ",
"  .        ...  ",
"  .        ...  ",
"  .     ........",
"  .     ........",
"  .     ........",
"  .        ...  ",
"  ............  ",
"           ...  ",
"                "};
static const char * color_new_xpm[] = {
"16 16 3 1",
" 	c None",
".	c #859900",
"@	c #FFFFFF",
"                ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@...  ",
"  @@@@@@@@@...  ",
"  @@@@@@@@@...  ",
"  @@@@@@........",
"  @@@@@@........",
"  @@@@@@........",
"  @@@@@@@@@...  ",
"  @@@@@@@@@...  ",
"           ...  ",
"                "};
static const char * color_open_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #000000",
"                ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  @@++++++++@@  ",
"  @@@@@@@@@@@@  ",
"  @@++++++++@@  ",
"  @@@@@@@@@@@@  ",
" .....@@@@@@@@  ",
" .............. ",
" .............. ",
" .............. ",
" .............. ",
" .............. ",
" .............. ",
"                "};
static const char * open_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"  ............  ",
"  .          .  ",
"  .          .  ",
"  . ........ .  ",
"  .          .  ",
"  . ........ .  ",
"  .          .  ",
" .....       .  ",
" .............. ",
" .............. ",
" .............. ",
" .............. ",
" .............. ",
" .............. ",
"                "};
static const char * save_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"   ..........   ",
"  ............  ",
"  ....    ....  ",
"  ....    ....  ",
"  ....    ....  ",
"  ....    ....  ",
"  ....    ....  ",
"  ..        ..  ",
"  ...      ...  ",
"  ....    ....  ",
"  .....  .....  ",
"  ............  ",
"  ............  ",
"  ............  ",
"   ..........   "};
static const char * color_save_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #68aee0",
"@	c #e8e7e7",
"+	c #268bd2",
"                ",
"   ..........   ",
"  ............  ",
"  ....@@@@....  ",
"  ....@@@@....  ",
"  ....@@@@....  ",
"  ....@@@@....  ",
"  ....@@@@....  ",
"  ..@@@@@@@@..  ",
"  ...@@@@@@...  ",
"  ....@@@@....  ",
"  .....@@.....  ",
"  ............  ",
"  +..........+  ",
"  ++++++++++++  ",
"   ++++++++++   "};
static const char * search_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"     ......     ",
"   ..........   ",
"  ....    ....  ",
"  ...      ...  ",
"  ...      ...  ",
"  ...      ...  ",
"  ....    ....  ",
"   ..........   ",
"     .......    ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * replace_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"     .......... ",
"   .....      . ",
"  .... . .... . ",
"  ...  .      . ",
"  ...  . .... . ",
"  ...  .      . ",
"  .... ........ ",
"   ..........   ",
"     ......     ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * color_search_xpm[] = {
"16 16 3 1",
" 	c None",
".	c #2aa198",
"@	c #e9f5f4",
"     ......     ",
"   ..........   ",
"  ....@@@@....  ",
"  ...@@@@@@...  ",
"  ...@@@@@@...  ",
"  ...@@@@@@...  ",
"  ....@@@@....  ",
"   ..........   ",
"     .......    ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * zoom_in_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"     ......     ",
"   ....... ...  ",
"  ....     ...  ",
"  ...   ........",
"  ...   ........",
"  ...      ...  ",
"  ....     ...  ",
"   .......      ",
"     .......    ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * color_zoom_in_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #2aa198",
"@	c #e9f5f4",
"#	c #859900",
"     ......     ",
"   .........##  ",
"  ....@@@@..##  ",
"  ...@@@########",
"  ...@@@########",
"  ...@@@@@@.##  ",
"  ....@@@@..##  ",
"   ..........   ",
"     .......    ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * zoom_out_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"     .......    ",
"   ...........  ",
"  ....          ",
"  ...   ........",
"  ...   ........",
"  ...           ",
"  ....    ....  ",
"   ...........  ",
"     .......    ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * color_zoom_out_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #2aa198",
"@	c #e9f5f4",
"#	c #cb4b16",
"     .......    ",
"   ...........  ",
"  ....@@@@....  ",
"  ...@@@########",
"  ...@@@########",
"  ...@@@@@@...  ",
"  ....@@@@....  ",
"   ..........   ",
"     .......    ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * color_replace_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #2aa198",
"@	c #e9f5f4",
"+	c #000000",
"-	c #ffffff",
"     ..-------- ",
"   ....-------- ",
"  ....@--++++-- ",
"  ...@@-------- ",
"  ...@@--++++-- ",
"  ...@@-------- ",
"  ....@-------- ",
"   ..........   ",
"     ......     ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"      ....      ",
"       ..       "};
static const char * color_undo_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #940000",
"                ",
"       .        ",
"      ..        ",
"     ...        ",
"    ........    ",
"   ..........   ",
"  ............  ",
"   ...........  ",
"    ..........  ",
"     ...   ...  ",
"      ..   ...  ",
"       .   ...  ",
"          ...   ",
"         ...    ",
"        ...     ",
"                "};
static const char * undo_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"       .        ",
"      ..        ",
"     ...        ",
"    ........    ",
"   ..........   ",
"  ............  ",
"   ...........  ",
"    ..........  ",
"     ...   ...  ",
"      ..   ...  ",
"       .   ...  ",
"          ...   ",
"         ...    ",
"        ...     ",
"                "};
static const char * settings_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"      ....      ",
"   .  ....  .   ",
"  ... .... ...  ",
" .............. ",
"  ............  ",
"   ....  ....   ",
"......    ......",
".....      .....",
".....      .....",
"......    ......",
"   ....  ....   ",
"  ............  ",
" .............  ",
"  ... .... ...  ",
"   .  ....  .   ",
"      ....      "};
#ifdef flpad_h
static const char * flpad_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #000000",
"-	c #940000",
"@	c #FFFFFF",
"                ",
"     ------     ",
"   ----------   ",
"  --@@@@@@@@--  ",
" ---@@@@@@@@--  ",
" ---@......@--- ",
" ---@@@@@@@@--- ",
" ---@....@@@--- ",
" ---@@@@@@@@--- ",
" ---@......@--- ",
" ---@@@@@@@@--- ",
"  --@......@--  ",
"  --@@@@@@@@--  ",
"   ----------   ",
"     ------     ",
"                "};
#endif
#ifdef flimage_h
static const char * flimage_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #000000",
"-	c #940000",
"@	c #FFFFFF",
"                ",
"     ------     ",
"   ----------   ",
"  --@@@@@@@@--  ",
" ---@......@--  ",
" ---@......@--- ",
" ---@......@--- ",
" ---@......@--- ",
"  --@......@--  ",
" ---@......@--- ",
" ---@@@@@@@@--- ",
" ---@@@@@@@@--- ",
"  --@@@@@@@@--  ",
"   ----------   ",
"     ------     ",
"                "};
#endif
#ifdef SciCalc_h
static const char * flcalc_xpm[] = {
"16 16 7 1",
" 	c None",
".	c #000000",
"-	c #940000",
"@	c #aaaaaa",
"#	c #FFFFFF",
"%  c #3fdabf",
"*  c #bfffbf",
"                ",
"     ------     ",
"   ----------   ",
"  --@@@@@@@@--  ",
" ---@******@--  ",
" ---@@@@@@@@--- ",
" ---@-@....@--- ",
" ---@#@#@#@@--- ",
" ---@@@@@@@@--- ",
" ---@###@%%@--- ",
" ---@###@%%@--- ",
" ---@###@%%@--- ",
"  --@@@@@@@@--  ",
"   ----------   ",
"     ------     ",
"                "};
#endif
static const char * docs_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #ed6a00",
"#	c #B17621",
"                ",
" ++++++++       ",
"++++++++++      ",
"+@@@@@@@@...... ",
"................",
"................",
"....########....",
"....#......#....",
"....########....",
"....#......#....",
"....########....",
"....#......#....",
"....########....",
"................",
"                ",
"                "};
static const char * music_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #ed6a00",
"#	c #B17621",
"                ",
" ++++++++       ",
"++++++++++      ",
"+@@@@@@@@...... ",
"................",
"................",
".....#######....",
".....#######....",
".....#.....#....",
".....#.....#....",
".....#.....#....",
"...###...###....",
"...##....##......",
"................",
"                ",
"                "};
static const char * videos_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #ed6a00",
"#	c #B17621",
"                ",
" ++++++++       ",
"++++++++++      ",
"+@@@@@@@@...... ",
"................",
"................",
"....########....",
"....#.####.#....",
"....########....",
"....#.####.#....",
"....########....",
"....#.####.#....",
"....########....",
"................",
"                ",
"                "};
static const char * pictures_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #ed6a00",
"#	c #B17621",
"                ",
" ++++++++       ",
"++++++++++      ",
"+@@@@@@@@...... ",
"................",
"....########....",
"....#......#....",
"....#.####.#....",
"....#.####.#....",
"....#.####.#....",
"....#......#....",
"....#......#....",
"....########....",
"................",
"                ",
"                "};
static const char * downloads_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #ed6a00",
"#	c #B17621",
"                ",
" ++++++++       ",
"++++++++++      ",
"+@@@@@@@@...... ",
"................",
"........#.......",
"........#.......",
"........#.......",
"......#####.....",
"....#..###..#...",
"....#...#...#...",
"....#.......#...",
"....#########...",
"................",
"                ",
"                "};
static const char * desktop_xpm[] = {
"16 16 5 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #ed6a00",
"#	c #B17621",
"                ",
" ++++++++       ",
"++++++++++      ",
"+@@@@@@@@...... ",
"................",
"..############..",
"..#..........#..",
"..#..####....#..",
"..#..#..#....#..",
"..#..####....#..",
"..#..........#..",
"..############..",
"......####......",
"....########....",
"................",
"                "};
static const char * flfm_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #ffa726",
"@	c #FFFFFF",
"+	c #ed6a00",
"                ",
" ++++++++       ",
"++++++++++      ",
"+@@@@@@@@...... ",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"                ",
"                "};
static const char * folder_xpm[] = {
"16 16 3 1",
" 	c None",
".	c #000000",
"+	c #000000",
"                ",
" ++++++++       ",
"++++++++++      ",
"+        ...... ",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"                ",
"                "};
static const char * color_file_xpm[] = {
"16 16 4 1",
" 	c None",
"@	c #DCDCDC",
"+	c #000000",
".	c #b1b1b1",
"                ",
"  @@@@@@.@@     ",
"  @@@@@@.@@@    ",
"  @@@@@@.@@@@   ",
"  @@@@@@......  ",
"  @@@@@@@@@...  ",
"  @@++++++++@.  ",
"  @@@@@@@@@@@@  ",
"  @@++++++++@@  ",
"  @@@@@@@@@@@@  ",
"  @@++++++++@@  ",
"  @@@@@@@@@@@@  ",
"  @@++++++++@@  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"                "};
static const char * home_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #000000",
"                ",
"      ...       ",
"     .....  ... ",
"    ....... ... ",
"   ............ ",
"  ............. ",
" .............. ",
"................",
"  ............  ",
"  ............  ",
"  ............  ",
"  ....    ....  ",
"  ....    ....  ",
"  ....    ....  ",
"  ....    ....  ",
"                "};
static const char * color_home_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #ffa726",
"                ",
"      ...       ",
"     .....  ... ",
"    ....... ... ",
"   ............ ",
"  ............. ",
" .............. ",
"................",
"  ............  ",
"  ............  ",
"  ............  ",
"  ....    ....  ",
"  ....    ....  ",
"  ....    ....  ",
"  ....    ....  ",
"                "};
static const char * color_trash_xpm[] = {
"16 16 2 1",
" 	c None",
".	c #B0B6C5",
"@	c #9297A3",
"#	c #687385",
"                ",
"     .......    ",
"     .......    ",
"     ..   ..    ",
"  ............. ",
"  ............. ",
"   @@#@@#@@#@@  ",
"   ..#..#..#..  ",
"   ..#..#..#..  ",
"   ..#..#..#..  ",
"   ..#..#..#..  ",
"   ..#..#..#..  ",
"   ...........  ",
"   ...........  ",
"                ",
"                "};
static const char * system_shutdown[] = {
"32 32 3 1",
" 	c None",
".	c #FF0000",
"+	c #FFFFFF",
"            ........            ",
"         ..............         ",
"       ..................       ",
"      ....................      ",
"     .........++++.........     ",
"    .......+..++++..+.......    ",
"   ......+++..++++..+++......   ",
"  ......++++..++++..++++.....   ",
"  .....+++++..++++..+++++.....  ",
" .....+++++...++++...+++++..... ",
" .....++++....++++....++++..... ",
" ....++++.....++++.....++++.... ",
".....++++.....++++.....++++.....",
".....+++......++++......+++.....",
"....++++......++++......++++....",
"....++++......++++......++++....",
"....++++................++++....",
"....++++................++++....",
".....+++................+++.....",
".....++++..............++++.....",
" ....++++..............++++.... ",
" .....++++............++++..... ",
" .....+++++..........+++++..... ",
"  .....++++++......++++++.....  ",
"  ......++++++++++++++++......  ",
"   ......++++++++++++++......   ",
"    .......++++++++++.......    ",
"     .........++++.........     ",
"      ....................      ",
"       ..................       ",
"         ..............         ",
"            ........            "};
static const char * system_restart[] = {
"32 32 3 1",
" 	c None",
".	c #859900",
"+	c #FFFFFF",
"            ........            ",
"         ..............         ",
"       ..................       ",
"      ....................      ",
"     ......................     ",
"    ........................    ",
"   .........++++++++.........   ",
"  ........++++++++++++........  ",
"  .......++++++++++++++.......  ",
" .......++++++++++++++++....... ",
" ......++++++......++++++...... ",
" .....+++++..........+++++++... ",
"......++++............++++++....",
"........++...........+++++++....",
"....................+++++++.....",
".....+++..............+++++.....",
".....+++++..............+++.....",
".....+++++++....................",
"....+++++++...........+.........",
"....++++++............++++......",
" ...+.+++++..........+++++..... ",
" ......++++++......++++++...... ",
" .......++++++++++++++++....... ",
"  .......++++++++++++++.......  ",
"  ........++++++++++++........  ",
"   .........++++++++.........   ",
"    ........................    ",
"     ......................     ",
"      ....................      ",
"       ..................       ",
"         ..............         ",
"            ........            "};
static const char * system_logout[] = {
"32 32 3 1",
" 	c None",
".	c #859900",
"+	c #FFFFFF",
"            ........            ",
"         ..............         ",
"       ..................       ",
"      ....................      ",
"     .........++++.........     ",
"    .......++++++++++.......    ",
"   ......++++++++++++++......   ",
"  ......++++++++++++++++......  ",
"  .....++++++......++++++.....  ",
" .....+++++..........+++++..... ",
" .....++++............++++..... ",
" ....++++..............++++.... ",
".......................++++.....",
"........................+++.....",
"....++++++++++++........++++....",
"....++++++++++++........++++....",
"....++++++++++++........++++....",
"....++++++++++++........++++....",
"........................+++.....",
".......................++++.....",
" ....++++..............++++.... ",
" .....++++............++++..... ",
" .....+++++..........+++++..... ",
"  .....++++++......++++++.....  ",
"  ......++++++++++++++++......  ",
"   ......++++++++++++++......   ",
"    .......++++++++++.......    ",
"     .........++++.........     ",
"      ....................      ",
"       ..................       ",
"         ..............         ",
"            ........            "};
static const char * system_hibernate[] = {
"32 32 3 1",
" 	c None",
".	c #645137",
"+	c #FFFFFF",
"                                ",
"           ..........           ",
"         ..............         ",
"       ..................       ",
"      ....................      ",
"     ......................     ",
"    ........................    ",
"   ..........................   ",
"   ............++............   ",
"  ............++++............  ",
"  ........+++.++++.+++........  ",
" .........++++++++++++......... ",
" .........++++++++++++......... ",
" ..........++++++++++.......... ",
" ........++++++++++++++........ ",
" .......++++++++++++++++....... ",
" .......++++++++++++++++....... ",
" ........++++++++++++++........ ",
" ..........++++++++++.......... ",
" .........++++++++++++......... ",
" .........++++++++++++......... ",
"  ........+++.++++.+++........  ",
"  ............++++............  ",
"   ............++............   ",
"   ..........................   ",
"    ........................    ",
"     ......................     ",
"      ....................      ",
"       ..................       ",
"         ..............         ",
"           ..........           ",
"                                "};
static const char * system_suspend[] = {
"32 32 3 1",
" 	c None",
".	c #FFBC2E",
"+	c #000000",
"                                ",
"           ..........           ",
"         ..............         ",
"       ..................       ",
"      ....................      ",
"     ......................     ",
"    ........................    ",
"   ..........................   ",
"   ..........................   ",
"  ............................  ",
"  ............................  ",
" ............++++++...........+ ",
" ..........++++++++++.......... ",
" ........++++......++++........ ",
" .......+++..........+++....... ",
" ......+++............+++...... ",
" .......+++..........++++...... ",
" ......++++++++++++++++++...... ",
" ......++..+++++++++++..+...... ",
" .........++...++...++......... ",
" ..............++.............+ ",
"  ............................  ",
"  ...........................+  ",
"   ..........................   ",
"   .........................+   ",
"    ........................    ",
"     ......................     ",
"      ....................      ",
"       .................+       ",
"         .............+         ",
"           +........+           ",
"                                "};

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
static Fl_Pixmap home_image(home_xpm);
static Fl_Pixmap folder_image(folder_xpm);

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
static Fl_Pixmap color_home_image(color_home_xpm);

static Fl_Pixmap color_folder_image(flfm_xpm);
static Fl_Pixmap color_file_image(color_file_xpm);

static Fl_Pixmap color_docs_image(docs_xpm);
static Fl_Pixmap color_videos_image(videos_xpm);
static Fl_Pixmap color_music_image(music_xpm);
static Fl_Pixmap color_pictures_image(pictures_xpm);
static Fl_Pixmap color_downloads_image(downloads_xpm);
static Fl_Pixmap color_desktop_image(desktop_xpm);
static Fl_Pixmap color_trash_image(color_trash_xpm);
// Power Management
static Fl_Pixmap shutdown_icon(system_shutdown);
static Fl_Pixmap restart_icon(system_restart);
static Fl_Pixmap suspend_icon(system_suspend);
static Fl_Pixmap hibernate_icon(system_hibernate);
static Fl_Pixmap logout_icon(system_logout);
