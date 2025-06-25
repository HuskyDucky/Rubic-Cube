/**
    File    : getch.h
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250622.0

    getch() wait for the user press any character to continue.
    This function is used on terminal on Linux.

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#ifndef GETCH_H
#define GETCH_H

#include <cstdio>
#include <unistd.h>
#include <termios.h>

int getch();

#endif // GETCH_H
