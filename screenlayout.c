#include "raylib.h"
#include "screenlayout.h"
#include "global.h"
#include <math.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

Texture2D score7Seg[10];

void InitializeScoreBoard()
{
    for (int i = 0; i < 10; i++)
    {
        score7Seg[i] = LoadTexture(TextFormat("res/timer-%d.png", i));
    }
}

void DrawMineSweeperBorders()
{
    // Draw light border
    DrawLineEx((Vector2){0, 0}, (Vector2){(SCREEN_WIDTH)*scaleFactor, 0}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){0, 1 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 1) * scaleFactor, 1 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){0, 2 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 2) * scaleFactor, 2 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){0, 0}, (Vector2){0, (SCREEN_HEIGHT)*scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){1 * scaleFactor, 0}, (Vector2){1 * scaleFactor, (SCREEN_HEIGHT)*scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){2 * scaleFactor, 0}, (Vector2){2 * scaleFactor, (SCREEN_HEIGHT)*scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});

    // Draw dark border
    DrawLineEx((Vector2){0, (SCREEN_HEIGHT)*scaleFactor}, (Vector2){(SCREEN_WIDTH)*scaleFactor, (SCREEN_HEIGHT)*scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){1 * scaleFactor, (SCREEN_HEIGHT - 1) * scaleFactor}, (Vector2){(SCREEN_WIDTH)*scaleFactor, (SCREEN_HEIGHT - 1) * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){2 * scaleFactor, (SCREEN_HEIGHT - 2) * scaleFactor}, (Vector2){(SCREEN_WIDTH)*scaleFactor, (SCREEN_HEIGHT - 2) * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){(SCREEN_WIDTH)*scaleFactor, 0}, (Vector2){(SCREEN_WIDTH)*scaleFactor, (SCREEN_HEIGHT)*scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){(SCREEN_WIDTH - 1) * scaleFactor, 1 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 1) * scaleFactor, (SCREEN_HEIGHT)*scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){(SCREEN_WIDTH - 2) * scaleFactor, 2 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 2) * scaleFactor, (SCREEN_HEIGHT)*scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
}

void DrawScoreBoardLayout()
{
    // Draw dark border
    DrawLineEx((Vector2){8 * scaleFactor, 8 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 9) * scaleFactor, 8 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){8 * scaleFactor, 9 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 10) * scaleFactor, 9 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){8 * scaleFactor, 10 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 11) * scaleFactor, 10 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){8 * scaleFactor, 8 * scaleFactor}, (Vector2){8 * scaleFactor, 57 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){9 * scaleFactor, 8 * scaleFactor}, (Vector2){9 * scaleFactor, 56 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){10 * scaleFactor, 8 * scaleFactor}, (Vector2){10 * scaleFactor, 55 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});

    // Draw light border

    DrawLineEx((Vector2){9 * scaleFactor, 55 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 9) * scaleFactor, 55 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){8 * scaleFactor, 56 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 9) * scaleFactor, 56 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){7 * scaleFactor, 57 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 9) * scaleFactor, 57 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){(SCREEN_WIDTH - 9) * scaleFactor, 58 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 9) * scaleFactor, 9 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){(SCREEN_WIDTH - 10) * scaleFactor, 58 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 10) * scaleFactor, 10 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){(SCREEN_WIDTH - 11) * scaleFactor, 58 * scaleFactor}, (Vector2){(SCREEN_WIDTH - 11) * scaleFactor, 11 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
}

void DrawScoreBorders()
{
    // Draw dark border
    DrawLineEx((Vector2){26 * scaleFactor, 14 * scaleFactor}, (Vector2){79 * scaleFactor, 14 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){26 * scaleFactor, 15 * scaleFactor}, (Vector2){78 * scaleFactor, 15 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){26 * scaleFactor, 16 * scaleFactor}, (Vector2){77 * scaleFactor, 16 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){26 * scaleFactor, 14 * scaleFactor}, (Vector2){26 * scaleFactor, 51 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){27 * scaleFactor, 14 * scaleFactor}, (Vector2){27 * scaleFactor, 50 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){28 * scaleFactor, 14 * scaleFactor}, (Vector2){28 * scaleFactor, 49 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});

    // Draw light border
    DrawLineEx((Vector2){25 * scaleFactor, 51 * scaleFactor}, (Vector2){79 * scaleFactor, 51 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){26 * scaleFactor, 50 * scaleFactor}, (Vector2){79 * scaleFactor, 50 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){27 * scaleFactor, 49 * scaleFactor}, (Vector2){79 * scaleFactor, 49 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){77 * scaleFactor, 51 * scaleFactor}, (Vector2){77 * scaleFactor, 17 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){78 * scaleFactor, 51 * scaleFactor}, (Vector2){78 * scaleFactor, 16 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){79 * scaleFactor, 51 * scaleFactor}, (Vector2){79 * scaleFactor, 15 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
}

void DrawTimerBorders()
{
    // Draw dark border
    DrawLineEx((Vector2){560 * scaleFactor, 14 * scaleFactor}, (Vector2){613 * scaleFactor, 14 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){560 * scaleFactor, 15 * scaleFactor}, (Vector2){612 * scaleFactor, 15 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){560 * scaleFactor, 16 * scaleFactor}, (Vector2){611 * scaleFactor, 16 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){560 * scaleFactor, 14 * scaleFactor}, (Vector2){560 * scaleFactor, 51 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){561 * scaleFactor, 14 * scaleFactor}, (Vector2){561 * scaleFactor, 50 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});
    DrawLineEx((Vector2){562 * scaleFactor, 14 * scaleFactor}, (Vector2){562 * scaleFactor, 49 * scaleFactor}, scaleFactor, (Color){84, 84, 84, 255});

    // Draw light border
    DrawLineEx((Vector2){559 * scaleFactor, 51 * scaleFactor}, (Vector2){613 * scaleFactor, 51 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){560 * scaleFactor, 50 * scaleFactor}, (Vector2){613 * scaleFactor, 50 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){561 * scaleFactor, 49 * scaleFactor}, (Vector2){613 * scaleFactor, 49 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){611 * scaleFactor, 51 * scaleFactor}, (Vector2){611 * scaleFactor, 17 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){612 * scaleFactor, 51 * scaleFactor}, (Vector2){612 * scaleFactor, 16 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
    DrawLineEx((Vector2){613 * scaleFactor, 51 * scaleFactor}, (Vector2){613 * scaleFactor, 15 * scaleFactor}, scaleFactor, (Color){148, 148, 148, 255});
}

void DrawScore(int score)
{
    int scoreOnes = score % 10;
    int scoreTens = (floor(score % 100)) / 10;
    Rectangle sourceRect1 = {0, 0, (float)score7Seg[scoreOnes].width, (float)score7Seg[scoreOnes].height};
    Rectangle destRect1 = {60.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[scoreOnes].width * scaleFactor, (float)score7Seg[scoreOnes].height * scaleFactor};
    Vector2 origin = {0, 0};
    DrawTexturePro(score7Seg[scoreOnes], sourceRect1, destRect1, origin, 0.0f, WHITE);

    Rectangle sourceRect10 = {0, 0, (float)score7Seg[scoreTens].width, (float)score7Seg[scoreTens].height};
    Rectangle destRect10 = {44.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[scoreTens].width * scaleFactor, (float)score7Seg[scoreTens].height * scaleFactor};
    DrawTexturePro(score7Seg[scoreTens], sourceRect10, destRect10, origin, 0.0f, WHITE);

    Rectangle sourceRect100 = {0, 0, (float)score7Seg[0].width, (float)score7Seg[0].height};
    Rectangle destRect100 = {28.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[0].width * scaleFactor, (float)score7Seg[0].height * scaleFactor};
    DrawTexturePro(score7Seg[0], sourceRect100, destRect100, origin, 0.0f, WHITE);
}

void DrawTimer(int seconds)
{
    if (seconds > 999)
    {
        Rectangle sourceRect1 = {0, 0, (float)score7Seg[9].width, (float)score7Seg[9].height};
        Rectangle destRect1 = {594.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[9].width * scaleFactor, (float)score7Seg[9].height * scaleFactor};
        Vector2 origin = {0, 0};
        DrawTexturePro(score7Seg[9], sourceRect1, destRect1, origin, 0.0f, WHITE);

        Rectangle sourceRect10 = {0, 0, (float)score7Seg[9].width, (float)score7Seg[9].height};
        Rectangle destRect10 = {578.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[9].width * scaleFactor, (float)score7Seg[9].height * scaleFactor};
        DrawTexturePro(score7Seg[9], sourceRect10, destRect10, origin, 0.0f, WHITE);

        Rectangle sourceRect100 = {0, 0, (float)score7Seg[9].width, (float)score7Seg[9].height};
        Rectangle destRect100 = {562.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[9].width * scaleFactor, (float)score7Seg[9].height * scaleFactor};
        DrawTexturePro(score7Seg[9], sourceRect100, destRect100, origin, 0.0f, WHITE);
    }
    else
    {
        int timerOnes = seconds % 10;
        int timerTens = (floor(seconds % 100)) / 10;
        int timerHundreds = seconds / 100;
        Rectangle sourceRect1 = {0, 0, (float)score7Seg[timerOnes].width, (float)score7Seg[timerOnes].height};
        Rectangle destRect1 = {594.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[timerOnes].width * scaleFactor, (float)score7Seg[timerOnes].height * scaleFactor};
        Vector2 origin = {0, 0};
        DrawTexturePro(score7Seg[timerOnes], sourceRect1, destRect1, origin, 0.0f, WHITE);

        Rectangle sourceRect10 = {0, 0, (float)score7Seg[timerTens].width, (float)score7Seg[timerTens].height};
        Rectangle destRect10 = {578.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[timerTens].width * scaleFactor, (float)score7Seg[timerTens].height * scaleFactor};
        DrawTexturePro(score7Seg[timerTens], sourceRect10, destRect10, origin, 0.0f, WHITE);

        Rectangle sourceRect100 = {0, 0, (float)score7Seg[timerHundreds].width, (float)score7Seg[timerHundreds].height};
        Rectangle destRect100 = {562.0f * scaleFactor, 17.0f * scaleFactor, (float)score7Seg[timerHundreds].width * scaleFactor, (float)score7Seg[timerHundreds].height * scaleFactor};
        DrawTexturePro(score7Seg[timerHundreds], sourceRect100, destRect100, origin, 0.0f, WHITE);
    }
}