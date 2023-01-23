//
// Created by Noran Raskin on 23.01.23.
//

#include "game.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

double scale_factor = 1.0;
#define WINDOW_WIDTH (800 * scale_factor)
#define WINDOW_HEIGHT (450 * scale_factor)

#define PADDLE_WIDTH (20 * scale_factor)
#define PADDLE_HEIGHT (80 * scale_factor)
#define PADDLE_SPEED (0.2 * scale_factor)

#define RANDOMFACTOR (6 * scale_factor)

#define FONTSIZE (30 * scale_factor)
#define TEXTOFFSET (30 * scale_factor)

#define BALL_SIZE (20 * scale_factor)
#define BALL_SPEED (0.1 * scale_factor)

void pvp(Rectangle * paddle, sBall _) {
    if (IsKeyDown(KEY_UP)) {
        paddle->y = fmax(paddle->y - PADDLE_SPEED,(double) 0);
    }
    if (IsKeyDown(KEY_DOWN)) {
        paddle->y = fmin(paddle->y + PADDLE_SPEED, WINDOW_HEIGHT - PADDLE_HEIGHT);
    }
}

void normal(Rectangle * paddle, sBall ball) {
    if (ball.speed.x < 0) {
        return;
    }
    time_t now = time(0);
    struct tm *tm;
    double offset;
    if ((tm = localtime(&now)) != NULL) {
        offset = (double) (tm->tm_sec % 10) * RANDOMFACTOR;
        if (((int)(tm->tm_sec /10)) & 1) {
            offset *= -1;
        }
    } else {
        offset = 0;
    }
    if (ball.pos.x < WINDOW_WIDTH / 2) {
        if (paddle->y + PADDLE_HEIGHT < WINDOW_HEIGHT/2) {
            paddle->y += PADDLE_SPEED/4;
        }
        if (paddle->y > WINDOW_HEIGHT/2) {
            paddle->y -= PADDLE_SPEED/4;
        }
    } else {
        if (paddle->y + PADDLE_HEIGHT/2 < ball.pos.y + offset) {
            paddle->y += PADDLE_SPEED/1.5;
        }
        if (paddle->y + PADDLE_HEIGHT/2 > ball.pos.y + offset) {
            paddle->y -= PADDLE_SPEED/1.5;
        }
        if(paddle->y < 0) paddle->y = 0;
        if(paddle->y > WINDOW_HEIGHT - PADDLE_HEIGHT) paddle->y = WINDOW_HEIGHT - PADDLE_HEIGHT;
    }
}

void hard(Rectangle * paddle, sBall ball) {
    if (paddle->y + PADDLE_HEIGHT/2 < ball.pos.y) {
        paddle->y += PADDLE_SPEED;
    }
    if (paddle->y + PADDLE_HEIGHT/2 > ball.pos.y) {
        paddle->y -= PADDLE_SPEED;
    }
    if(paddle->y < 0) paddle->y = 0;
    if(paddle->y > WINDOW_HEIGHT - PADDLE_HEIGHT) paddle->y = WINDOW_HEIGHT - PADDLE_HEIGHT;
}

void game(GameMode mode) {
    // Initialize the window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");

    // Initialize the paddles
    Rectangle leftPaddle = { 10, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT };
    Rectangle rightPaddle = { WINDOW_WIDTH - PADDLE_WIDTH - 10, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT };

    // Initialize the ball
    sBall ball = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, BALL_SPEED, BALL_SPEED};
    void (*updateRightPaddle) (Rectangle* paddle, sBall ball);
    switch (mode) {
        case PVP:
            updateRightPaddle = pvp;
            break;
        case NORMAL:
            updateRightPaddle = normal;
            break;
        case HARD:
            updateRightPaddle = hard;
            break;
    }
    // Initialize the scores
    int leftScore = 0;
    int rightScore = 0;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update player paddle
        if (IsKeyDown(KEY_W)) {
            leftPaddle.y = fmaxf(leftPaddle.y - PADDLE_SPEED, 0);
        }
        if (IsKeyDown(KEY_S)) {
            leftPaddle.y = fminf(leftPaddle.y + PADDLE_SPEED, WINDOW_HEIGHT - PADDLE_HEIGHT);
        }
        updateRightPaddle(&rightPaddle, ball);

        ball.pos.x += ball.speed.x;
        ball.pos.y += ball.speed.y;

        // Check for collisions with the paddles
        if (CheckCollisionRecs(leftPaddle, (Rectangle){ball.pos.x, ball.pos.y, BALL_SIZE, BALL_SIZE })) {
            ball.speed.x = fabsf(ball.speed.x);
        }
        if (CheckCollisionRecs(rightPaddle, (Rectangle){ball.pos.x, ball.pos.y, BALL_SIZE, BALL_SIZE })) {
            ball.speed.x = -fabsf(ball.speed.x);
        }

        // Check for collisions with the walls
        if (ball.pos.y <0 || ball.pos.y > WINDOW_HEIGHT - BALL_SIZE) ball.speed.y *= -1;

        // Check for scoring
        if (ball.pos.x < 0)
        {
            rightScore++;
            ball.pos = (Vector2){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
            ball.speed = (Vector2){BALL_SPEED, BALL_SPEED };
        }
        else if (ball.pos.x > WINDOW_WIDTH) {
            leftScore++;
            ball.pos = (Vector2) {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
            ball.speed = (Vector2) {-BALL_SPEED, -BALL_SPEED};
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleRec(leftPaddle, WHITE);
        DrawRectangleRec(rightPaddle, WHITE);
        DrawCircleV(ball.pos, BALL_SIZE / 2, WHITE);
        // Draw the scores
        char scoreText[32];
        sprintf(scoreText, "%d : %d", leftScore, rightScore);
        DrawText(scoreText, WINDOW_WIDTH/2 - MeasureText(scoreText, FONTSIZE)/2, TEXTOFFSET, FONTSIZE, WHITE);

        EndDrawing();
    }

    // Close the window
    CloseWindow();
}
