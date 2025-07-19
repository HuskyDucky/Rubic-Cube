/**
    File    : debug.h
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250718.0

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#ifndef TESTS_H
#define TESTS_H

#include "../lib/getch.h"
#include "../rubik_cube/rubik.h"

const char* desc(colors::to dir);

const char* pos(colors::to dir);

#endif // TESTS_H
