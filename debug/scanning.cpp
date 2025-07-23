/**
    File    : debug_scanning.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250719.1

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "debug.h"

struct s_facescanned
{
    position face_scanned;
    string face_colors;
};

void execute_scanning_and_show_results(rubik& cube, const s_facescanned& f, const scan_status ExpRes) {

    const scan_status Result = cube.scan(f.face_scanned, f.face_colors);    // GET RESULT

    const auto desc_pos = [](const position face) -> const char* {

        switch (face) {
            case position::Left   : return "left  ";
            case position::Top    : return "top   ";
            case position::Front  : return "front ";
            case position::Back   : return "back  ";
            case position::Bottom : return "bottom";
            case position::Right  : return "right ";
            default :               return "ERROR ";
        }
    };

    const auto desc_scan_status = [](const scan_status desc) -> const string {
        switch(desc) {
            case scan_status::FACE_SCANNED                  : return "face scanned";
            case scan_status::INCONSISTENT_FACE_SIZE        : return "fail to create the block";
            case scan_status::UNEXPECTED_COLOR_FOUND        : return "unexpected color found";
//            case scan_status::BLK_INCONSISTENT_QT_OF_COLORS : return "inconsistent qt of colors";
//            case scan_status::REPEATED_COLOR_IN_BLK         : return "repeated color in the block";
//            case scan_status::BLK_WITH_INCOMPATIBLE_COLORS  : return "incompatible color found in the block";
            case scan_status::CUBE_MALFORMED                : return "cube is malformed and can't be updated";
            case scan_status::UNDEFINED_ERROR               : return "undefined error";
            case scan_status::CUBE_FORMED_AND_UPDATED       : return "cube is formed and updated";
            default                                         : return "DESC ERROR";
        }
    };

    const auto paint_letters = [](const string& face_colors) -> const string {
        uint8_t Max = face_colors.size() < 255 ? face_colors.size() : 255;

        string lp;
        lp.reserve(Max * 24); // every letter will receive the codification for paint. Its size may reach 24 bytes per letter

        for (uint8_t c = 0; c < Max; c++)
            lp += coloring(static_cast<char>(face_colors[c]));

        return lp;
    };

    const auto show_result = [&]() -> string {
        if (Result == ExpRes)
            return "\x1B[92mPassed\033[0m";

        ostringstream tmp;
        tmp << "\x1B[91mFail\033[0m\n     Expected: [" << ExpRes << " - " << desc_scan_status(ExpRes) << ']';

        return tmp.str();
    };

    cout << "\nface scanned : [" << desc_pos(f.face_scanned) << ']'
         << "\n     colors  : [" << paint_letters(f.face_colors) << ']'
         << "\n     Result  : [" << Result << " - " << desc_scan_status(Result) << "] " << show_result();
}

void chk_memory_during_scanning() {
    s_facescanned faces[6] = { {position::Front , "WWWWWWWWW"},
                               {position::Top   , "RRRRRRRRR"},
                               {position::Right , "GGGGGGGGG"},
                               {position::Left  , "BBBBBBBBB"},
                               {position::Bottom, "OOOOOOOOO"},
                               {position::Back  , "YYYYYYYYY"} };
    rubik cube; // create a 3x3x3 cube

    cout << "\n\nTemporary cube before scan faces (it is expected to be empty):\n\n";
    cube.show_Scan_mem();

    for (uint8_t n = 0; n < 5; n++)
        execute_scanning_and_show_results(cube, faces[n], scan_status::FACE_SCANNED);

    cout << "\n\nShow temporary cube without scan the back face ([Y]ellow color):\n\n";
    cube.show_Scan_mem();

    execute_scanning_and_show_results(cube, faces[5], scan_status::CUBE_FORMED_AND_UPDATED);

    cout << "\n\nTemporary cube after scan faces (it is expected to be empty):\n\n";
    cube.show_Scan_mem();

    getch();
}

void chk_face_size() {
    cout << "\n\nCheck scanning faces with inconsistent size:\n\n";

    s_facescanned faces[6] = { {position::Front , "WWWWWWWWW"},
                               {position::Top   , "RRRRRRRR"},
                               {position::Right , "GGGGGGGGGG"},
                               {position::Left  , ""},
                               {position::Bottom, "OOOOOOOOOOOOOOOO"},
                               {position::Back  , "YYYYYYYYY"} };
    rubik cube; // create a 3x3x3 cube

   execute_scanning_and_show_results(cube, faces[0], scan_status::FACE_SCANNED);
   execute_scanning_and_show_results(cube, faces[1], scan_status::INCONSISTENT_FACE_SIZE);
   execute_scanning_and_show_results(cube, faces[2], scan_status::INCONSISTENT_FACE_SIZE);
   execute_scanning_and_show_results(cube, faces[3], scan_status::INCONSISTENT_FACE_SIZE);
   execute_scanning_and_show_results(cube, faces[4], scan_status::INCONSISTENT_FACE_SIZE);
   execute_scanning_and_show_results(cube, faces[5], scan_status::FACE_SCANNED);

    cout << "\n\nTemporary cube after scan (it is expected to have only front[W] and back[Y] faces scanned):\n\n";
    cube.show_Scan_mem();

    getch();
}

void chk_expected_colors_and_rescan() {
    s_facescanned faces[10] = { {position::Front , "wWWW WWWw"},
                                {position::Top   , "RrrrRRrRR"},
                                {position::Right , "GGGGGGGGG"},
                                {position::Left  , "BBBBBBZBB"},
                                {position::Bottom, "OO OOOOOO"},
                                {position::Back  , "TYYYYYYYY"},
                                {position::Bottom, "OOOOOOOOO"},    // rescan
                                {position::Back  , "YYYYYYYYY"},    // rescan
                                {position::Front , "wWWWWWWWw"},    // rescan
                                {position::Left  , "BBBBBBBBB"} };  // rescan
    rubik cube; // create a 3x3x3 cube

    cout << "\n\nCheck scanning faces with inexistent colors and upper lower case:\n\n";

   execute_scanning_and_show_results(cube, faces[0], scan_status::UNEXPECTED_COLOR_FOUND);
   execute_scanning_and_show_results(cube, faces[1], scan_status::FACE_SCANNED);
   execute_scanning_and_show_results(cube, faces[2], scan_status::FACE_SCANNED);
   execute_scanning_and_show_results(cube, faces[3], scan_status::UNEXPECTED_COLOR_FOUND);
   execute_scanning_and_show_results(cube, faces[4], scan_status::UNEXPECTED_COLOR_FOUND);
   execute_scanning_and_show_results(cube, faces[5], scan_status::UNEXPECTED_COLOR_FOUND);

    cout << "\n\nTemporary cube after scan (it is expected to have only top[R] and right[G] faces scanned):\n\n";
    cube.show_Scan_mem();

    execute_scanning_and_show_results(cube, faces[6], scan_status::FACE_SCANNED);
    execute_scanning_and_show_results(cube, faces[7], scan_status::FACE_SCANNED);
    execute_scanning_and_show_results(cube, faces[8], scan_status::FACE_SCANNED);
    execute_scanning_and_show_results(cube, faces[9], scan_status::CUBE_FORMED_AND_UPDATED);

    getch();
}

void chk_uniqueness_colors_in_blocks() {
    s_facescanned faces[6] = { {position::Front , "WWWWWWWWW"},
                               {position::Top   , "RRRRRRRRR"}, // <-
                               {position::Right , "GGYGGGGGG"},
                               {position::Left  , "BBBBBBBBB"},
                               {position::Bottom, "OOOOOOOOO"},
                               {position::Back  , "YYYYYYYYY"} };
    rubik cube; // create a 3x3x3 cube

    cout << "\n\nTemporary cube before scan faces (it is expected to be empty):\n\n";

    for (uint8_t c = 0; c < 6; c++)
        execute_scanning_and_show_results(cube, faces[c], c == 5 ? scan_status::CUBE_MALFORMED : scan_status::FACE_SCANNED);

    getch();
}

void chk_colors_position_consistency() {
    s_facescanned faces[6] = { {position::Front , "YWWWWWWWW"},     // <-
                               {position::Top   , "RRRRRRRRR"},
                               {position::Right , "GGGGGGGGG"},
                               {position::Left  , "BOBBBBGBB"},     // <-
                               {position::Bottom, "OOOOOOOOO"},
                               {position::Back  , "YYYYYYYYW"} };   // <-
    rubik cube; // create a 3x3x3 cube

    for (uint8_t c = 0; c < 6; c++)
        execute_scanning_and_show_results(cube, faces[c], c == 5 ? scan_status::CUBE_MALFORMED : scan_status::FACE_SCANNED);

    getch();
}

void chk_malformed_cube()
{
    s_facescanned faces[6] = { {position::Front , "WWWWWWWWW"},
                               {position::Top   , "RRRRRRRRR"},
                               {position::Right , "GGGGGGGGG"},
                               {position::Left  , "BOBBBBBBB"},
                               {position::Bottom, "OBOOOOOOO"},     //<- malformed cube
                               {position::Back  , "YYYYYYYYY"} };
     rubik cube; // create a 3x3x3 cube

    for (uint8_t c = 0; c < 6; c++)
        execute_scanning_and_show_results(cube, faces[c], c == 5 ? scan_status::CUBE_MALFORMED : scan_status::FACE_SCANNED);

    getch();
}

void chk_color_compatibility() {
    s_facescanned faces[6] = { {position::Front , "YWWWWWWWW"},
                               {position::Top   , "RRRRRRRRR"},
                               {position::Right , "GGGGGGGGG"},
                               {position::Left  , "BOBBBBBBB"},     //<- malformed cube
                               {position::Bottom, "OBOOOOOOO"},     //<- malformed cube
                               {position::Back  , "YYYYYYYYW"} };
     rubik cube; // create a 3x3x3 cube

    for (uint8_t c = 0; c < 6; c++)
        execute_scanning_and_show_results(cube, faces[c], c == 5 ? scan_status::CUBE_MALFORMED : scan_status::FACE_SCANNED);

    getch();
}

void chk_valid_random_cube() {
//        s_facescanned faces[6] = { {position::Front , "ROGRYGGGW"},
//                                   {position::Top   , "grbyogbbr"},
//                                   {position::Right , "YryYGyogG"},
//                                   {position::Left  , "WBWWBWYRW"},
//                                   {position::Bottom, "OOBYRWRWO"},
//                                   {position::Back  , "OBROWOYBB"} };
        s_facescanned faces[6] = { {position::Front , "WOWOBWggW"},
                                   {position::Top   , "rWGYRGGYG"},
                                   {position::Right , "OyOGWOOYY"},
                                   {position::Left  , "WRRRYwBWY"},
                                   {position::Bottom, "RRBBOBOOb"},
                                   {position::Back  , "YGRBGBBRY"} };
     rubik cube; // create a 3x3x3 cube

    for (uint8_t c = 0; c < 6; c++)
        execute_scanning_and_show_results(cube, faces[c], c == 5 ? scan_status::CUBE_FORMED_AND_UPDATED : scan_status::FACE_SCANNED);

    cout << "\n\nTemporary cube after scan faces (it is expected to be empty):\n\n";
    cube.show_Scan_mem();

    cube.show();

    getch();
}

void scanning()
{
    //chk_memory_during_scanning();
    //chk_face_size();
    //chk_expected_colors_and_rescan();
    //chk_uniqueness_colors_in_blocks();
    //chk_color_compatibility();
    //chk_colors_position_consistency();
    //chk_malformed_cube();
    chk_valid_random_cube();
}
