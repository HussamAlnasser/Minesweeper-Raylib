#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "screenlayout.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui/src/raygui.h"
#include "global.h"
#include "buttons.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

Board mainBoard;
int difficulty;
bool reset;

float scaleFactor;

float prevScaleFactorChoice;

int scaleFactorChoice;

void static InitializeGameBoard();
void static PrintGrid();

Image mineSweeperIcon;

bool initialized = false;

int score = 40;
int actualScore = 40;
int timer = 0;
int frameCount = 0;
bool stopTimer = false;

int main()
{
    srand(time(0));

    reset = false;

    mineSweeperIcon = LoadImage("res/msweepericon.png");
    scaleFactor = 1;
    scaleFactorChoice = 0;
    prevScaleFactorChoice = 0;

    InitWindow(SCREEN_WIDTH * scaleFactor, SCREEN_HEIGHT * scaleFactor, "Minesweeper");

    SetWindowIcon(mineSweeperIcon);
    SetTargetFPS(60);

    Color minesweeperBG = {46, 46, 46, 255};

    score = 40;
    actualScore = 40;

    // int dropdownActive = 1;
    bool dropdownEditMode = false;
    bool dropdownEditMode2 = false;
    GuiSetStyle(DEFAULT, TEXT_SIZE, 10 * scaleFactor);
    difficulty = BEGINNER;

    while (!WindowShouldClose())
    {
        ClearBackground(minesweeperBG);
        if (!initialized || reset)
        {
            if (scaleFactorChoice != prevScaleFactorChoice)
            {
                prevScaleFactorChoice = scaleFactorChoice;

                scaleFactor = scaleFactorChoice + 1;

                SetWindowSize(SCREEN_WIDTH * scaleFactor, SCREEN_HEIGHT * scaleFactor);
                GuiSetStyle(DEFAULT, TEXT_SIZE, 10 * scaleFactor);
            }
            InitializeScoreBoard();
            if (difficulty == BEGINNER)
            {
                score = 10;
                actualScore = 10;
            }
            else if (difficulty == EXPERT)
            {
                score = 99;
                actualScore = 99;
            }
            else
            {
                score = 40;
                actualScore = 40;
            }
            InitializeGameBoard();
            InitializeMainButtons();
            InitializeGridButtons();
            timer = 0;
            stopTimer = false;
            frameCount = 0;
            initialized = true;
            reset = false;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            CheckGButtonClickEvents(GetMousePosition());
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            CheckGButtonRightClickEvents(GetMousePosition());
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            CheckGButtonUnclickEvents(GetMousePosition());
        }
        if (frameCount % 60 == 0 && frameCount != 0 && !stopTimer)
        {
            timer++;
        }
        if (timer < 999 || stopTimer)
        {
            frameCount++;
        }

        // GRAPHICS GOES HERE
        BeginDrawing();

        DrawMineSweeperBorders();

        DrawScoreBoardLayout();

        DrawScoreBorders();

        DrawTimerBorders();

        DrawScore(score);

        DrawTimer(timer);

        DrawDefaultButtons();

        DrawGridButtons();

        if (GuiDropdownBox((Rectangle){412 * scaleFactor, 18 * scaleFactor, 96 * scaleFactor, 32 * scaleFactor}, "BEGINNER;INTERMEDIATE;EXPERT", &difficulty, dropdownEditMode))
        {
            dropdownEditMode = !dropdownEditMode;
            reset = true;
        }

        if (GuiDropdownBox((Rectangle){130 * scaleFactor, 18 * scaleFactor, 96 * scaleFactor, 32 * scaleFactor}, "360p;720p;1080p", &scaleFactorChoice, dropdownEditMode2))
        {
            dropdownEditMode2 = !dropdownEditMode2;
            reset = true;
        }

        EndDrawing();
        // GRAPHICS ENDS HERE
    }

    if (initialized)
    {
        FreeGraphMemory();
    }

    CloseWindow();
}

void InitializeGameBoard()
{
    int numberOfBombs = 0;

    if (difficulty == BEGINNER)
    {
        mainBoard.height = 9;
        mainBoard.width = 9;
        numberOfBombs = 10;
    }
    else if (difficulty == EXPERT)
    {
        mainBoard.height = 16;
        mainBoard.width = 30;
        numberOfBombs = 99;
    }
    else
    {
        mainBoard.height = 16;
        mainBoard.width = 16;
        numberOfBombs = 40;
    }

    int arraySize = mainBoard.width * mainBoard.height;

    if (mainBoard.grid == NULL)
    {
        mainBoard.grid = (int *)malloc(arraySize * sizeof(int));
    }
    else
    {
        int *temp = (int *)realloc(mainBoard.grid, arraySize * sizeof(int));

        if (temp != NULL)
        {
            mainBoard.grid = temp;
        }
    }
    // Plant bombs
    // BEGINNER 10
    // INTERMEDIATE 40
    // EXPERT 99
    for (int i = 0; i < arraySize; i++)
    {
        mainBoard.grid[i] = 0;
    }
    for (int i = 1; i <= numberOfBombs; i++)
    {
        bool moveOn = false;
        while (!moveOn)
        {
            int bombLoc = rand() % arraySize;
            if (mainBoard.grid[bombLoc] != -1)
            {
                moveOn = true;
                mainBoard.grid[bombLoc] = -1;

                // Track Neighbors
                int x = bombLoc % mainBoard.width;
                int y = bombLoc / mainBoard.width;

                for (int j = y - 1; j <= y + 1; j++)
                {
                    if (j < 0 || j >= mainBoard.height)
                    {
                        continue;
                    }
                    for (int k = x - 1; k <= x + 1; k++)
                    {
                        if (k < 0 || k >= mainBoard.width)
                        {
                            continue;
                        }
                        int newLoc = (j * mainBoard.width) + (k % mainBoard.width);
                        if (mainBoard.grid[newLoc] != -1)
                        {
                            mainBoard.grid[newLoc]++;
                        }
                    }
                }
            }
        }
    }
}

void PrintGrid()
{
    printf("[");
    for (int i = 0; i < (mainBoard.height); i++)
    {
        for (int j = 0; j < mainBoard.width; j++)
        {
            int newLoc = (i * mainBoard.width) + (j % mainBoard.width);
            printf("%d, ", mainBoard.grid[newLoc]);
        }
        printf("\n");
    }
    printf("]");
}