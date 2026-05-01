#include <raylib.h>
#include "global.h"
#include "buttons.h"
#include <stdio.h>
#include <math.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

GButton *mainButtons;
GButton *gridButtons;

Texture2D blockUnpressed;
Texture2D blockPressed;
Texture2D mineLanded;
Texture2D mineNotLanded;
Texture2D numberBlocks[8];
Texture2D blockFlagged;

Texture2D smilyFaceUnpressed;
Texture2D smilyFacePressed;
Texture2D loseFaceUnpressed;
Texture2D loseFacePressed;
Texture2D winFaceUnpressed;
Texture2D winFacePressed;

int mouseDownGridIndex = -1;
int mouseDownMainIndex = -1;
int mainButtonsLength = 1;

void ClearOpenSpaces(int spaceIndex, int previousIndex)
{
    int column = spaceIndex % mainBoard.width;
    int row = spaceIndex / mainBoard.width;

    if (mainBoard.grid[spaceIndex] == 0)
    {
        gridButtons[spaceIndex].textureNoClick = &blockPressed;
        gridButtons[spaceIndex].textureOnClick = &blockPressed;
        gridButtons[spaceIndex].clicked = true;
        for (int i = row - 1; i <= row + 1; i++)
        {
            if (i < 0 || i >= mainBoard.height)
            {
                continue;
            }
            for (int j = column - 1; j <= column + 1; j++)
            {
                if (j < 0 || j >= mainBoard.width)
                {
                    continue;
                }
                int newLoc = (i * mainBoard.width) + (j % mainBoard.width);
                if (previousIndex != newLoc)
                {
                    if (mainBoard.grid[newLoc] != -1)
                    {
                        if (gridButtons[newLoc].textureNoClick != &blockPressed)
                        {
                            ClearOpenSpaces(newLoc, spaceIndex);
                        }
                    }
                }
            }
        }
    }
    else
    {
        gridButtons[spaceIndex].textureNoClick = &numberBlocks[mainBoard.grid[spaceIndex] - 1];
        gridButtons[spaceIndex].textureOnClick = &numberBlocks[mainBoard.grid[spaceIndex] - 1];
        gridButtons[spaceIndex].clicked = true;
    }
}

void GameOverProcedure(int wrongStepIndex)
{
    int arraySize = mainBoard.width * mainBoard.height;
    for (int i = 0; i < arraySize; i++)
    {
        if (wrongStepIndex != i)
        {
            if (mainBoard.grid[i] == -1)
            {
                gridButtons[i].textureNoClick = &mineNotLanded;
                gridButtons[i].textureOnClick = &mineNotLanded;
            }
        }
        gridButtons[i].clicked = true;
    }
    mainButtons[0].textureNoClick = &loseFaceUnpressed;
    mainButtons[0].textureOnClick = &loseFacePressed;
    stopTimer = true;
}

void WinProcedure()
{
    int arraySize = mainBoard.width * mainBoard.height;
    for (int i = 0; i < arraySize; i++)
    {
        gridButtons[i].clicked = true;
    }
    mainButtons[0].textureNoClick = &winFaceUnpressed;
    mainButtons[0].textureOnClick = &winFacePressed;
    stopTimer = true;
}

void MouseDownMainButtonEvent(int buttonIndex)
{
    mouseDownMainIndex = buttonIndex;
    mouseDownGridIndex = -1;
}

void MouseUpMainButtonEvent(int buttonIndex)
{
    reset = true;
    mouseDownMainIndex = -1;
}

void MouseDownGridButtonEvent(int buttonIndex)
{
    if (!gridButtons[buttonIndex].flagged && !gridButtons[buttonIndex].clicked)
    {
        mouseDownGridIndex = buttonIndex;
        mouseDownMainIndex = -1;
    }
}

void MouseUpGridButtonEvent(int buttonIndex)
{
    if (!gridButtons[buttonIndex].flagged && !gridButtons[buttonIndex].clicked)
    {
        gridButtons[buttonIndex].clicked = true;
        if (mainBoard.grid[buttonIndex] == -1)
        {
            gridButtons[buttonIndex].textureNoClick = &mineLanded;
            gridButtons[buttonIndex].textureOnClick = &mineLanded;

            GameOverProcedure(buttonIndex);
        }
        else if (mainBoard.grid[buttonIndex] == 0)
        {
            int column = buttonIndex % mainBoard.width;
            int row = buttonIndex / mainBoard.width;
            gridButtons[buttonIndex].textureNoClick = &blockPressed;
            gridButtons[buttonIndex].textureOnClick = &blockPressed;

            for (int j = row - 1; j <= row + 1; j++)
            {
                if (j < 0 || j >= mainBoard.height)
                {
                    continue;
                }
                for (int k = column - 1; k <= column + 1; k++)
                {
                    if (k < 0 || k >= mainBoard.width)
                    {
                        continue;
                    }
                    int newLoc = (j * mainBoard.width) + (k % mainBoard.width);
                    if (mainBoard.grid[newLoc] != -1)
                    {
                        if (gridButtons[newLoc].textureNoClick != &blockPressed)
                        {
                            ClearOpenSpaces(newLoc, buttonIndex);
                        }
                    }
                }
            }
        }
        else
        {
            gridButtons[buttonIndex].textureNoClick = &numberBlocks[mainBoard.grid[buttonIndex] - 1];
            gridButtons[buttonIndex].textureOnClick = &numberBlocks[mainBoard.grid[buttonIndex] - 1];
        }
    }
}

void RightGridButtonEvent(int buttonIndex)
{
    if (!gridButtons[buttonIndex].flagged && !gridButtons[buttonIndex].clicked && score > 0)
    {
        gridButtons[buttonIndex].flagged = true;
        gridButtons[buttonIndex].textureNoClick = &blockFlagged;
        score--;
        if (mainBoard.grid[buttonIndex] == -1)
        {
            actualScore--;
            if (actualScore <= 0)
            {
                WinProcedure();
            }
        }
    }
    else if (gridButtons[buttonIndex].flagged && !gridButtons[buttonIndex].clicked)
    {
        gridButtons[buttonIndex].flagged = false;
        gridButtons[buttonIndex].textureNoClick = &blockUnpressed;
        score++;
        if (mainBoard.grid[buttonIndex] == -1)
        {
            actualScore++;
        }
    }
}

void InitializeMainButtons()
{
    if (smilyFaceUnpressed.id <= 0)
    {
        smilyFaceUnpressed = LoadTexture("res/smily-face-unpressed.png");
    }
    if (smilyFacePressed.id <= 0)
    {
        smilyFacePressed = LoadTexture("res/smily-face-pressed.png");
    }
    if (loseFaceUnpressed.id <= 0)
    {
        loseFaceUnpressed = LoadTexture("res/lose-face-unpressed.png");
    }
    if (loseFacePressed.id <= 0)
    {
        loseFacePressed = LoadTexture("res/lose-face-pressed.png");
    }

    if (winFaceUnpressed.id <= 0)
    {
        winFaceUnpressed = LoadTexture("res/win-face-unpressed.png");
    }
    if (winFacePressed.id <= 0)
    {
        winFacePressed = LoadTexture("res/win-face-pressed.png");
    }

    if (mainButtons == NULL)
    {
        mainButtons = (GButton *)malloc(mainButtonsLength * sizeof(GButton));
    }
    else
    {
        GButton *temp = (GButton *)realloc(mainButtons, mainButtonsLength * sizeof(GButton));

        if (temp != NULL)
        {
            mainButtons = temp;
        }
    }

    mainButtons[0].type = OTHER_BTN;
    mainButtons[0].textureNoClick = &smilyFaceUnpressed;
    mainButtons[0].textureOnClick = &smilyFacePressed;
    mainButtons[0].position = (Rectangle){(float)304 * scaleFactor, (float)18 * scaleFactor,
                                          (float)mainButtons[0].textureNoClick->width * scaleFactor, (float)mainButtons[0].textureNoClick->height * scaleFactor};
    mainButtons[0].clicked = false;
    mainButtons[0].flagged = false;
    mainButtons[0].clickEvent = MouseDownMainButtonEvent;
    mainButtons[0].unclickEvent = MouseUpMainButtonEvent;
}

void InitializeGridButtons()
{
    if (blockUnpressed.id <= 0)
    {
        blockUnpressed = LoadTexture("res/block-unpressed.png");
    }
    if (blockPressed.id <= 0)
    {
        blockPressed = LoadTexture("res/block-pressed.png");
    }
    if (mineLanded.id <= 0)
    {
        mineLanded = LoadTexture("res/mine-landed.png");
    }
    if (mineNotLanded.id <= 0)
    {
        mineNotLanded = LoadTexture("res/mine-not-landed.png");
    }
    if (blockFlagged.id <= 0)
    {
        blockFlagged = LoadTexture("res/flag.png");
    }

    for (int i = 0; i < 8; i++)
    {
        if (numberBlocks[i].id <= 0)
        {
            numberBlocks[i] = LoadTexture(TextFormat("res/number-%d.png", i + 1));
        }
    }

    int arraySize = mainBoard.width * mainBoard.height;

    if (gridButtons == NULL)
    {
        gridButtons = (GButton *)malloc(arraySize * sizeof(GButton));
    }
    else
    {
        GButton *temp = (GButton *)realloc(gridButtons, arraySize * sizeof(GButton));

        if (temp != NULL)
        {
            gridButtons = temp;
        }
    }

    int centerOfGridY = (int)floor((((float)mainBoard.height) / 2.0f) * blockUnpressed.height) + 59;
    if (difficulty != BEGINNER)
    {
        centerOfGridY = (int)16 + 59;
    }

    int centerOfGridX = (int)(SCREEN_WIDTH / 2) - floor((((float)mainBoard.width) / 2.0f) * blockUnpressed.width);

    for (int i = 0; i < arraySize; i++)
    {
        int column = i % mainBoard.width;
        int height = i / mainBoard.width;
        gridButtons[i].type = GRID_BTN;
        gridButtons[i].textureNoClick = &blockUnpressed;
        gridButtons[i].textureOnClick = &blockPressed;
        gridButtons[i].position = (Rectangle){(float)(column * gridButtons[i].textureNoClick->width * scaleFactor) + ((float)centerOfGridX * scaleFactor), (float)(height * gridButtons[i].textureNoClick->height * scaleFactor) + ((float)centerOfGridY * scaleFactor),
                                              (float)gridButtons[i].textureNoClick->width * scaleFactor, (float)gridButtons[i].textureNoClick->height * scaleFactor};
        gridButtons[i].clicked = false;
        gridButtons[i].flagged = false;
        gridButtons[i].clickEvent = MouseDownGridButtonEvent;
        gridButtons[i].unclickEvent = MouseUpGridButtonEvent;
        gridButtons[i].rightClickEvent = RightGridButtonEvent;
    }
}

void CheckGButtonClickEvents(Vector2 mousePos)
{
    // Main buttons event
    bool pressedMainButton = false;
    for (int i = 0; i < mainButtonsLength; i++)
    {
        if (CheckCollisionPointRec(mousePos, mainButtons[i].position))
        {
            mainButtons[0].clickEvent((int)i);
            pressedMainButton = true;
            break;
        }
    }
    // Main board events
    if (!pressedMainButton)
    {
        int arraySize = mainBoard.width * mainBoard.height;
        for (int i = 0; i < arraySize; i++)
        {
            if (CheckCollisionPointRec(mousePos, gridButtons[i].position))
            {
                gridButtons[i].clickEvent(i);
                break;
            }
        }
    }
}

void CheckGButtonUnclickEvents(Vector2 mousePos)
{
    // Main buttons event
    bool pressedMainButton = false;
    for (int i = 0; i < mainButtonsLength; i++)
    {
        if (CheckCollisionPointRec(mousePos, mainButtons[i].position))
        {
            mainButtons[0].unclickEvent((int)i);
            pressedMainButton = true;
            break;
        }
    }
    // Main board events
    if (!pressedMainButton)
    {
        int arraySize = mainBoard.width * mainBoard.height;
        for (int i = 0; i < arraySize; i++)
        {
            if (CheckCollisionPointRec(mousePos, gridButtons[i].position))
            {
                gridButtons[i].unclickEvent(i);
                break;
            }
        }
    }
}

void CheckGButtonRightClickEvents(Vector2 mousePos)
{
    // Main buttons event
    bool pressedMainButton = false;
    // Main board events
    if (!pressedMainButton)
    {
        int arraySize = mainBoard.width * mainBoard.height;
        for (int i = 0; i < arraySize; i++)
        {
            if (CheckCollisionPointRec(mousePos, gridButtons[i].position))
            {
                gridButtons[i].rightClickEvent(i);
                break;
            }
        }
    }
}

void DrawDefaultButtons()
{
    for (int i = 0; i < mainButtonsLength; i++)
    {
        Rectangle sourceRect1 = {0, 0, (float)mainButtons[i].textureOnClick->width, (float)mainButtons[i].textureOnClick->height};

        Vector2 origin = {0, 0};

        if (mouseDownMainIndex == (int)i)
        {
            DrawTexturePro(*mainButtons[i].textureOnClick, sourceRect1, mainButtons[i].position, origin, 0.0f, WHITE);
        }
        else
        {
            DrawTexturePro(*mainButtons[i].textureNoClick, sourceRect1, mainButtons[i].position, origin, 0.0f, WHITE);
        }
    }
}

void DrawGridButtons()
{
    int arraySize = mainBoard.width * mainBoard.height;
    for (int i = 0; i < arraySize; i++)
    {
        Rectangle sourceRect1 = {0, 0, (float)gridButtons[i].textureOnClick->width, (float)gridButtons[i].textureOnClick->height};

        Vector2 origin = {0, 0};

        if (mouseDownGridIndex == i)
        {
            DrawTexturePro(*gridButtons[i].textureOnClick, sourceRect1, gridButtons[i].position, origin, 0.0f, WHITE);
        }
        else
        {
            DrawTexturePro(*gridButtons[i].textureNoClick, sourceRect1, gridButtons[i].position, origin, 0.0f, WHITE);
        }
    }
    int indexfirstColLastRow = (mainBoard.height - 1) * mainBoard.width;
    int indexLastColLastRow = (mainBoard.height * mainBoard.width) - 1;

    // Draw dark border
    DrawLineEx((Vector2){(gridButtons[0].position.x - (3 * scaleFactor)), (gridButtons[0].position.y - (3 * scaleFactor))}, (Vector2){((gridButtons[mainBoard.width - 1].position.x) + (gridButtons[mainBoard.width - 1].textureNoClick->width * scaleFactor) + (3 * scaleFactor)), (gridButtons[mainBoard.width - 1].position.y - (3 * scaleFactor))}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){(gridButtons[0].position.x - (3 * scaleFactor)), (gridButtons[0].position.y - (2 * scaleFactor))}, (Vector2){((gridButtons[mainBoard.width - 1].position.x) + (gridButtons[mainBoard.width - 1].textureNoClick->width * scaleFactor) + (2 * scaleFactor)), (gridButtons[mainBoard.width - 1].position.y - (2 * scaleFactor))}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){(gridButtons[0].position.x - (3 * scaleFactor)), (gridButtons[0].position.y - (1 * scaleFactor))}, (Vector2){((gridButtons[mainBoard.width - 1].position.x) + (gridButtons[mainBoard.width - 1].textureNoClick->width * scaleFactor) + (1 * scaleFactor)), (gridButtons[mainBoard.width - 1].position.y - (1 * scaleFactor))}, scaleFactor, (Color){84, 84, 84, 255});

    DrawLineEx((Vector2){(gridButtons[0].position.x - (2 * scaleFactor)), (gridButtons[0].position.y - (3 * scaleFactor))}, (Vector2){(gridButtons[indexfirstColLastRow].position.x - (3 * scaleFactor)), ((gridButtons[indexfirstColLastRow].position.y) + (gridButtons[indexfirstColLastRow].textureNoClick->width * scaleFactor) + (2 * scaleFactor))}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){(gridButtons[0].position.x - (1 * scaleFactor)), (gridButtons[0].position.y - (3 * scaleFactor))}, (Vector2){(gridButtons[indexfirstColLastRow].position.x - (2 * scaleFactor)), ((gridButtons[indexfirstColLastRow].position.y) + (gridButtons[indexfirstColLastRow].textureNoClick->width * scaleFactor) + (1 * scaleFactor))}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){(gridButtons[0].position.x), (gridButtons[0].position.y - (3 * scaleFactor))}, (Vector2){(gridButtons[indexfirstColLastRow].position.x - (1 * scaleFactor)), ((gridButtons[indexfirstColLastRow].position.y) + (gridButtons[indexfirstColLastRow].textureNoClick->width * scaleFactor))}, scaleFactor, (Color){84, 84, 84, 255});

    // Draw light border
    DrawLineEx((Vector2){(gridButtons[indexfirstColLastRow].position.x - (1 * scaleFactor)), ((gridButtons[indexfirstColLastRow].position.y) + (gridButtons[indexfirstColLastRow].textureNoClick->height * scaleFactor))}, (Vector2){((gridButtons[indexLastColLastRow].position.x) + (gridButtons[indexLastColLastRow].textureNoClick->width * scaleFactor) + (3 * scaleFactor)), ((gridButtons[indexLastColLastRow].position.y) + (gridButtons[indexLastColLastRow].textureNoClick->height * scaleFactor))}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){(gridButtons[indexfirstColLastRow].position.x - (2 * scaleFactor)), ((gridButtons[indexfirstColLastRow].position.y) + (gridButtons[indexfirstColLastRow].textureNoClick->height * scaleFactor) + (1 * scaleFactor))}, (Vector2){((gridButtons[indexLastColLastRow].position.x) + (gridButtons[indexLastColLastRow].textureNoClick->width * scaleFactor) + (3 * scaleFactor)), ((gridButtons[indexLastColLastRow].position.y) + (gridButtons[indexLastColLastRow].textureNoClick->height * scaleFactor) + (1 * scaleFactor))}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){(gridButtons[indexfirstColLastRow].position.x - (3 * scaleFactor)), ((gridButtons[indexfirstColLastRow].position.y) + (gridButtons[indexfirstColLastRow].textureNoClick->height * scaleFactor) + (2 * scaleFactor))}, (Vector2){((gridButtons[indexLastColLastRow].position.x) + (gridButtons[indexLastColLastRow].textureNoClick->width * scaleFactor) + (3 * scaleFactor)), ((gridButtons[indexLastColLastRow].position.y) + (gridButtons[indexLastColLastRow].textureNoClick->height * scaleFactor) + (2 * scaleFactor))}, scaleFactor, (Color){148, 148, 148, 255});

    DrawLineEx((Vector2){((gridButtons[indexLastColLastRow].position.x) + (gridButtons[indexLastColLastRow].textureNoClick->width * scaleFactor) + (1 * scaleFactor)), ((gridButtons[indexLastColLastRow].position.y) + (gridButtons[indexLastColLastRow].textureNoClick->height * scaleFactor) + (2 * scaleFactor))}, (Vector2){((gridButtons[mainBoard.width - 1].position.x) + (gridButtons[mainBoard.width - 1].textureNoClick->width * scaleFactor) + (1 * scaleFactor)), (gridButtons[mainBoard.width - 1].position.y)}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){((gridButtons[indexLastColLastRow].position.x) + (gridButtons[indexLastColLastRow].textureNoClick->width * scaleFactor) + (2 * scaleFactor)), ((gridButtons[indexLastColLastRow].position.y) + (gridButtons[indexLastColLastRow].textureNoClick->height * scaleFactor) + (2 * scaleFactor))}, (Vector2){((gridButtons[mainBoard.width - 1].position.x) + (gridButtons[mainBoard.width - 1].textureNoClick->width * scaleFactor) + (2 * scaleFactor)), ((gridButtons[mainBoard.width - 1].position.y) - (1 * scaleFactor))}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){((gridButtons[indexLastColLastRow].position.x) + (gridButtons[indexLastColLastRow].textureNoClick->width * scaleFactor) + (3 * scaleFactor)), ((gridButtons[indexLastColLastRow].position.y) + (gridButtons[indexLastColLastRow].textureNoClick->height * scaleFactor) + (2 * scaleFactor))}, (Vector2){((gridButtons[mainBoard.width - 1].position.x) + (gridButtons[mainBoard.width - 1].textureNoClick->width * scaleFactor) + (3 * scaleFactor)), ((gridButtons[mainBoard.width - 1].position.y) - (2 * scaleFactor))}, scaleFactor, (Color){148, 148, 148, 255});
}

void FreeGraphMemory()
{
    if (mainButtons != NULL)
    {
        free(mainButtons);
        mainButtons = NULL;
    }
    if (gridButtons != NULL)
    {
        free(gridButtons);
        gridButtons = NULL;
    }
    UnloadTexture(blockUnpressed);
    UnloadTexture(blockPressed);
    UnloadTexture(smilyFaceUnpressed);
    UnloadTexture(smilyFacePressed);
    UnloadTexture(loseFaceUnpressed);
    UnloadTexture(loseFacePressed);
    UnloadTexture(mineLanded);
    UnloadTexture(mineNotLanded);
    UnloadTexture(blockFlagged);
    for (int i = 0; i < 8; i++)
    {
        UnloadTexture(numberBlocks[i]);
    }
}