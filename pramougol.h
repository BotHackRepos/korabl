#pragma once
#pragma once
#ifndef PRAMOUGOL_H
#define PRAMOUGOL_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <share.h>
#include <conio.h>
#define WIDTH 120
#define HEIGHT 30
#else
#include <sys/types.h>
#include <sys/sockets.h>
#include <termios.h>
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 25
#endif



#define LEFT_AND_UP 1
#define CENTER_AND_UP 2
#define RIGHT_AND_UP 3
#define CENTER_AND_LEFT 4
#define CENTER 5
#define CENTER_AND_RIGHT 6
#define DOWN_AND_LEFT 7
#define DOWN_AND_CENTER 8
#define DOWN_AND_RIGHT 9
#define FULLDIR "FULL"
#define CUBNODIR "NO FULL"
#define LEFT_POZITION '<'
#define RIGHT_POZITION '>'
#define UP_POZITION '^'
#define DOWN_POZITION 'v'
#define GETPOZITION 'g'
#define MINUS '-'
#define PLUS '+'
int GHEIGHT(int POL)
{
    return HEIGHT / 4 * POL;
}

int GWIDTH(int POLL)
{
    return WIDTH / 4 * POLL;
}

struct Pramougol {
    int bl = 0;
    int x[2];
    int y[2];
    Pramougol(int param) {
        switch (param) {
        case LEFT_AND_UP:
            y[0] = 0, y[1] = HEIGHT / 4, x[0] = 0, x[1] = WIDTH / 4;
            break;
        case CENTER_AND_UP:
            y[0] = 0, y[1] = HEIGHT, x[0] = GWIDTH(2), x[1] = GWIDTH(3);
            break;
        case RIGHT_AND_UP:
            y[0] = 0, y[1] = GHEIGHT(2), x[0] = GWIDTH(2), x[1] = GWIDTH(4);
            break;
        case CENTER_AND_LEFT:
            y[0] = GHEIGHT(2), y[1] = GHEIGHT(3), x[0] = 0, x[1] = GWIDTH(2);
            break;
        case CENTER:
            y[0] = GHEIGHT(2), y[1] = GHEIGHT(3), x[0] = GWIDTH(2), x[1] = GWIDTH(3);
            break;
        case CENTER_AND_RIGHT:
            y[0] = GHEIGHT(2), y[1] = GHEIGHT(3), x[0] = GWIDTH(3), x[1] = GWIDTH(4);
            break;
        case DOWN_AND_LEFT:
            y[0] = GHEIGHT(3), y[1] = GHEIGHT(4), x[0] = 0, x[1] = GWIDTH(2);
            break;
        case DOWN_AND_CENTER:
            y[0] = GHEIGHT(3), y[1] = GHEIGHT(4), x[0] = GWIDTH(2), x[1] = GWIDTH(3);
            break;
        case DOWN_AND_RIGHT:
            y[0] = GHEIGHT(3), y[1] = GHEIGHT(4), x[0] = GWIDTH(3), x[1] = GWIDTH(4);
            break;
        default:
            bl = 1;
            perror("ERROR: ");
            printf("error of calling CUB::CUB()\n");
        }
    }
    void View() {
        const char* param = (const char*)FULLDIR;
        if (bl == 0) {
            for (int i = 0; i < HEIGHT; ++i) {
                for (int j = 0; j < WIDTH; ++j) {
                    if (i >= y[0] && i <= y[1] && j >= x[0] && j <= x[1]) {
                        printf("%s", "*");
                    }
                    else if (i > y[1] || j > x[1]) {
                        if (param == (const char*)FULLDIR) {
                            printf("%s", " ");
                        }
                        else if (param == (const char*)CUBNODIR) {
                            return;
                        }
                    }
                    else {
                        printf("%s", " ");
                    }
                }
            }
        }
    }
    void UpdateDirection(char pol)
    {
        if (bl == 0)
        {
            switch (pol)
            {
            case GETPOZITION:
#ifdef _WIN32
                pol = _getch();
#else
                pol = getch();
#endif
            case LEFT_POZITION:
                --x[0];
                --x[1];
                break;
            case RIGHT_POZITION:
                ++x[0];
                ++x[1];
                break;
            case UP_POZITION:
                --y[0];
                --y[1];
                break;
            case DOWN_POZITION:
                ++y[0];
                ++y[1];
                break;
            default:
                bl = 1;
                perror("ERROR: ");
                printf("error of calling void CUB::UpdateDirection()\n");
            }
        }
    }
    void EditSizeOfCub(char ed) {
        if (bl == 0) {
            if (ed == MINUS) {
                ++x[0];
                --x[1];
                ++y[0];
                --y[1];
            }
            else if (ed == PLUS) {
                --x[0];
                ++x[1];
                --y[0];
                ++y[1];
            }
            else {
                bl = 1;
                perror("ERROR: ");
                printf("error of calling CUB::EditSizeOfCub()\n");
            }
        }
    }
};

#define NOPRIKOSPR 0
#define PRIKOSPR 1
#define ERRORCODE -1

int PrikosPramougols(Pramougol* ptr, Pramougol* ptr2)//если 1 - то прикосаются, если 0 - то не прикосаются, если другое - ошибка
{
    srand(time(0));
    if (ptr->bl == 0) {
        for (int i = 0; i < HEIGHT; ++i)
        {
            for (int j = 0; j < WIDTH; ++j)
            {
                if ((i >= ptr->y[0] && i <= ptr->y[1] && j >= ptr->x[0] && j <= ptr->x[1]) && (i >= ptr2->y[0] && i <= ptr2->y[1] && j >= ptr2->x[0] && j <= ptr2->x[1]))
                {
                    return PRIKOSPR;
                }
            }
        }
    }
    else {
        return ERRORCODE;
    }
    return NOPRIKOSPR;
}