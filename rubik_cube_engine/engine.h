/**
    File    : engine.h
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
/*
    TO DO:
        resolve: 1st turn cube to right position
*/
#ifndef ENGINE_H
#define ENGINE_H

#include <cinttypes>
#include <cstring>
#include <cmath>

#include <vector>
#include <forward_list>
#include <list>

#include <iostream>

#include "general.h"
#include "class_color.h"

using namespace std;

using CubeT = vector<vector<vector<colors>>>;

struct history
{
    colors::to direction;
    uint8_t xyz;
};

enum scan_status : uint16_t {
    FACE_SCANNED,
    INCONSISTENT_FACE_SIZE,
    UNEXPECTED_COLOR_FOUND,
    CUBE_MALFORMED,
    //BLK_INCONSISTENT_QT_OF_COLORS,

    //REPEATED_COLOR_IN_BLK,
    //BLK_WITH_INCOMPATIBLE_COLORS,
    UNDEFINED_ERROR,
    CUBE_FORMED_AND_UPDATED
};

struct rubik_engine
{
    rubik_engine();
    rubik_engine(uint8_t Cube_Size);

    void spin(const colors::to direction, const uint8_t xyz);   // xyz starts at 0 and the last value is the cube size -1.
                                                                // (ex.: for cube(3) xyz must be >= 0 and < 3)

    uint16_t size() const;

    const list<history>& get_Spin_history() const;

    void reset();
    void recreate(const uint8_t Cube_Size);

    scan_status scan(const position face_scanned, const string& face_colors);   // To scan the cube correctly just fix its front face and turn around it around
                                                                                // valid colors are [W]hite, [Y]ellow, [B]lue, [O]range, [R]ed and [G]reen
                                                                                // obs.: the scan is case insensitive
    protected:

        colors block(uint8_t line, uint8_t column, uint8_t layer) const;
        #ifdef DEBUG
            colors blockDebugScan(uint8_t line, uint8_t column, uint8_t layer) const;
            uint16_t DebugScan_size() const;
        #endif // DEBUG

    private:
        uint8_t CS;    // cube size

        colors auxSpin;  // help the spin_ functions
        inline void spin_right(const uint8_t x);
        inline void spin_left(const uint8_t x);
        inline void spin_up(const uint8_t y);
        inline void spin_down(const uint8_t y);
        inline void spin_clockwise(const uint8_t z);
        inline void spin_anticlockwise(const uint8_t z);

        list<history> spin_history;
        CubeT CUBE;

        uint8_t scan_facesScanned; // auxiliate the function scan
        forward_list<colors> scan_cube_validation; //vector<pair<color, bool>> scan_cube_validation;

        //inline bool scan_is_qt_of_colors_inconsistent(colors& S, const uint8_t lyr, const uint8_t lin, const uint8_t col);
        inline void scan_add_face_scanned_to_Sube(const position face_scanned, const string& face_colors);
        //inline bool scan_has_invalid_color_position(const colors& S, forward_list<colors>& chk_blk);

        CubeT Sube; // scanned cube
};

#endif // ENGINE_H
