/**
    File    : engine_scan.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250723.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "engine.h"

bool scan_inconpatible_colors(const char curr, const char next);

scan_status rubik_engine::scan(const position face_scanned, const string& face_colors)
{
    if (face_colors.size() != pow(CUBE.size(), 2))
        return scan_status::INCONSISTENT_FACE_SIZE;

    if (face_colors.find_first_not_of("WYBORGwyborg") != string::npos)
        return scan_status::UNEXPECTED_COLOR_FOUND;

    scan_add_face_scanned_to_Sube(face_scanned, face_colors);

    scan_facesScanned |= (1 << face_scanned);   // register all faces scanned

    if (scan_facesScanned != 63)                // check if all faces (value 63) were scanned
        return FACE_SCANNED;

    forward_list<colors> chk_blk(scan_cube_validation);

    for (uint8_t lyr = 0; lyr <= CS; lyr++)
        for (uint8_t lin = 0; lin <= CS; lin++)
            for (uint8_t col = 0; col <= CS; col++)
                if (lyr == 0 || lyr == CS || col == 0 || col == CS || lin == 0 || lin == CS)    // it is a colored block
                {
                    colors& S = Sube[lyr][lin][col];

                    //if (scan_is_qt_of_colors_inconsistent(S, lyr, lin, col))    // also uppercase the scanned face's colors
                    //    return BLK_INCONSISTENT_QT_OF_COLORS;
                    for (uint8_t c = 0; c < 6; c++)
                        if (S.in[c] != ' ')
                            S.in[c] &= ~' ';   // uppercase

//                    for (uint16_t c = 0; c < 5; c++)
//                        for (uint16_t r = c + 1; r < 6; r++)
//                            if (S.in[c] != ' ')
//                            {
//                                if (S.in[c] == S.in[r])
//                                    return REPEATED_COLOR_IN_BLK;

//                                if ((S.in[c] == 'W' && S.in[r] == 'Y') ||
//                                    (S.in[c] == 'Y' && S.in[r] == 'W') ||
//                                    (S.in[c] == 'B' && S.in[r] == 'G') ||
//                                    (S.in[c] == 'G' && S.in[r] == 'B') ||
//                                    (S.in[c] == 'R' && S.in[r] == 'O') ||
//                                    (S.in[c] == 'O' && S.in[r] == 'R'))
//                                    return BLK_WITH_INCOMPATIBLE_COLORS;
//                            }

                    auto has_invalid_color_position = [&]() -> bool {
                        auto prev = chk_blk.before_begin();
                        for (auto C = chk_blk.begin(); C != chk_blk.end(); ++C)
                        {
                            for (uint8_t tUp = 0; tUp < 4; tUp++) {
                                for (uint8_t tRight = 0; tRight < 4; tRight++) {
                                    for (uint8_t tClockWise = 0; tClockWise < 4; tClockWise++) {
                                        if (memcmp(S.in, C->in, 6 * sizeof(char)) == 0)
                                        {
                                            chk_blk.erase_after(prev);
                                            return false;
                                        }
                                        C->spin(colors::to::clockwise);
                                    }
                                    C->spin(colors::to::right);
                                }
                                C->spin(colors::to::up);
                            }
                            prev = C;
                        }

                        return true;
                    };

                    if (has_invalid_color_position())
                        return CUBE_MALFORMED;
                }

    if (chk_blk.empty())
    {
        CUBE = Sube;

        for (uint8_t lyr = 0; lyr <= CS; lyr++)
            for (uint8_t lin = 0; lin <= CS; lin++)
                for (uint8_t col = 0; col <= CS; col++)
                {
                    memcpy(CUBE[lyr][lin][col].in, Sube[lyr][lin][col].in, 6 * sizeof(char));
                    memset(Sube[lyr][lin][col].in, ' ', 6 * sizeof(char));
                }

        scan_facesScanned = 0;
        spin_history.clear();

        return CUBE_FORMED_AND_UPDATED;
    }

    return UNDEFINED_ERROR;
}

inline void rubik_engine::scan_add_face_scanned_to_Sube(const position face_scanned, const string& face_colors)
{
    switch (face_scanned) {
        case position::Left   : for (uint8_t lyr = 0; lyr <= CS; lyr++)
                                    for (uint8_t lin = 0; lin <= CS; lin++)
                                        Sube[lyr][lin][0].in[position::Left] = face_colors[CS - lyr + lin * CUBE.size()];
                                break;
        case position::Top    : for (uint8_t lyr = 0; lyr <= CS; lyr++)
                                    for (uint8_t col = 0; col <= CS; col++)
                                        Sube[lyr][0][col].in[position::Top] = face_colors[col + (CS - lyr) * CUBE.size()];
                                break;
        case position::Front  : for (uint8_t lin = 0; lin <= CS; lin++)
                                    for (uint8_t col = 0; col <= CS; col++)
                                        Sube[0][lin][col].in[position::Front] = face_colors[col + lin * CUBE.size()];
                                break;
        case position::Back   : for (uint8_t lin = 0; lin <= CS; lin++)
                                    for (uint8_t col = 0; col <= CS; col++)
                                        Sube[CS][lin][col].in[position::Back] = face_colors[col + (CS - lin) * CUBE.size()];
                                break;
        case position::Bottom : for (uint8_t lyr = 0; lyr <= CS; lyr++)
                                    for (uint8_t col = 0; col <= CS; col++)
                                        Sube[lyr][CS][col].in[position::Bottom] = face_colors[col + lyr * CUBE.size()];
                                break;
        case position::Right  : for (uint8_t lyr = 0; lyr <= CS; lyr++)               // ERROR! NEED TO BE FIXED
                                    for (uint8_t lin = 0; lin <= CS; lin++)
                                        Sube[lyr][lin][CS].in[position::Right] = face_colors[lyr + lin * CUBE.size()];
                                break;
    }
}

//inline bool rubik_engine::scan_is_qt_of_colors_inconsistent(colors& S, const uint8_t lyr, const uint8_t lin, const uint8_t col)
//{
//    bool isLyrEdge = lyr == 0 || lyr == CS;
//    bool isLinEdge = lin == 0 || lin == CS;
//    bool isColEdge = col == 0 || col == CS;
//
//    uint8_t QtLettersExpected = 2;
//
//    if (isLyrEdge && isLinEdge && isColEdge)            QtLettersExpected = 3;      // edges
//    else if ((isLyrEdge && !isLinEdge && !isColEdge) ||                             // center front, back
//             (!isLyrEdge && !isLinEdge && isColEdge) ||                             // center left, right
//             (!isLyrEdge && isLinEdge && !isColEdge))   QtLettersExpected = 1;      // center top, bottom
//    else if (!isLyrEdge && !isLinEdge && !isColEdge)    QtLettersExpected = 0;      // cube center
//
//    uint8_t not_space = 0;
//    for (uint8_t c = 0; c < 6; c++)
//        if (S.in[c] != ' ')
//        {
//            if (++not_space > QtLettersExpected)
//                return true;
//
//            S.in[c] &= ~' ';   // uppercase
//        }
//
//    return false;
//}

//inline bool rubik_engine::scan_has_invalid_color_position(const colors& S, forward_list<colors>& chk_blk)
//{
//    auto prev = chk_blk.before_begin();
//    for (auto C = chk_blk.begin(); C != chk_blk.end(); ++C)
//    {
//        for (uint8_t tUp = 0; tUp < 4; tUp++) {
//            for (uint8_t tRight = 0; tRight < 4; tRight++) {
//                for (uint8_t tClockWise = 0; tClockWise < 4; tClockWise++) {
//                    if (memcmp(S.in, C->in, 6 * sizeof(char)) == 0)
//                    {
//                        chk_blk.erase_after(prev);
//                        return false;
//                    }
//                    C->spin(colors::to::clockwise);
//                }
//                C->spin(colors::to::right);
//            }
//            C->spin(colors::to::up);
//        }
//        prev = C;
//    }
//
//    return true;
//}
