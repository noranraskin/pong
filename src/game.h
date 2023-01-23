//
// Created by Noran Raskin on 23.01.23.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H
#include <raylib.h>

typedef struct {
    Vector2 pos;
    Vector2 speed;
} sBall;

typedef struct {
    Rectangle paddle;
    int Score;
} sPaddle;

typedef enum {
    PVP,
    NORMAL,
    HARD
} GameMode;

void game(GameMode);
void pvp(Rectangle *, sBall);
void normal(Rectangle *, sBall);
void hard(Rectangle *, sBall);
#endif //PONG_GAME_H