#ifndef GLOBAL_H
#define GLOBAL_H
#include "raylib.h"

typedef struct
{
    int *grid;
    int width;
    int height;

} Board;

enum GameMode
{
    BEGINNER = 0,
    INTERMEDIATE = 1,
    EXPERT = 2
};

extern Board mainBoard;
extern int difficulty;
extern bool reset;

extern float scaleFactor;

extern int score;
extern int actualScore;

extern bool stopTimer;

#endif