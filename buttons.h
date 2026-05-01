#ifndef BUTTONS_H
#define BUTTONS_H

#include "raylib.h"

enum BtnTypes
{
    GRID_BTN = 0,
    OTHER_BTN = 1
};

typedef struct _GButton
{
    int type;
    Texture2D *textureNoClick;
    Texture2D *textureOnClick;
    bool clicked;
    bool flagged;
    Rectangle position;
    void (*clickEvent)(int buttonIndex);
    void (*unclickEvent)(int buttonIndex);
    void (*rightClickEvent)(int buttonIndex);

} GButton;

extern int mouseDownMainIndex;
extern int mouseDownGridIndex;

extern GButton *mainButtons;
extern GButton *gridButtons;

extern Texture2D blockUnpressed;
extern Texture2D blockPressed;
extern Texture2D mineLanded;
extern Texture2D mineNotLanded;
extern Texture2D blockFlagged;
extern Texture2D numberBlocks[8];
extern Texture2D smilyFaceUnpressed;
extern Texture2D smilyFacePressed;
extern Texture2D loseFaceUnpressed;
extern Texture2D loseFacePressed;
extern Texture2D winFaceUnpressed;
extern Texture2D winFacePressed;

void InitializeMainButtons();
void InitializeGridButtons();
void CheckGButtonClickEvents(Vector2 mousePos);
void CheckGButtonUnclickEvents(Vector2 mousePos);
void CheckGButtonRightClickEvents(Vector2 mousePos);
void DrawDefaultButtons();
void DrawGridButtons();
void FreeGraphMemory();

#endif