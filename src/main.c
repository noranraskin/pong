// main.c

#include "main.h"
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 80
#define PADDLE_SPEED 0.2

#define FONTSIZE 30

#define BALL_SIZE 20
#define BALL_SPEED 0.1

int main(void) {
    // Initialize the window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");

    // Initialize the paddles
    Rectangle leftPaddle = { 10, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT };
    Rectangle rightPaddle = { WINDOW_WIDTH - PADDLE_WIDTH - 10, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT };

    // Initialize the ball
    Vector2 ballPos = { WINDOW_WIDTH/2, WINDOW_HEIGHT/2 };
    Vector2 ballSpeed = { BALL_SPEED, BALL_SPEED };

    // Initialize the scores
    int leftScore = 0;
    int rightScore = 0;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyDown(KEY_W)) {
            leftPaddle.y = fmaxf(leftPaddle.y - PADDLE_SPEED, 0);
        }
        if (IsKeyDown(KEY_S)) {
            leftPaddle.y = fminf(leftPaddle.y + PADDLE_SPEED, WINDOW_HEIGHT - PADDLE_HEIGHT);
        }
        if (IsKeyDown(KEY_UP)) {
            rightPaddle.y = fmaxf(rightPaddle.y - PADDLE_SPEED, 0);
        }
        if (IsKeyDown(KEY_DOWN)) {
            rightPaddle.y = fminf(rightPaddle.y + PADDLE_SPEED, WINDOW_HEIGHT - PADDLE_HEIGHT);
        }

        ballPos.x += ballSpeed.x;
        ballPos.y += ballSpeed.y;

        // Check for collisions with the paddles
        if (CheckCollisionRecs(leftPaddle, (Rectangle){ ballPos.x, ballPos.y, BALL_SIZE, BALL_SIZE })) {
            ballSpeed.x = fabsf(ballSpeed.x);
        }
        if (CheckCollisionRecs(rightPaddle, (Rectangle){ ballPos.x, ballPos.y, BALL_SIZE, BALL_SIZE })) {
            ballSpeed.x = -fabsf(ballSpeed.x);
        }

        // Check for collisions with the walls
        if (ballPos.y < 0 || ballPos.y > WINDOW_HEIGHT - BALL_SIZE) ballSpeed.y *= -1;

        // Check for scoring
        if (ballPos.x < 0)
        {
            rightScore++;
            ballPos = (Vector2){ WINDOW_WIDTH/2, WINDOW_HEIGHT/2 };
            ballSpeed = (Vector2){ BALL_SPEED, BALL_SPEED };
        }
        else if (ballPos.x > WINDOW_WIDTH) {
            leftScore++;
            ballPos = (Vector2) {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
            ballSpeed = (Vector2) {-BALL_SPEED, -BALL_SPEED};
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleRec(leftPaddle, WHITE);
        DrawRectangleRec(rightPaddle, WHITE);
        DrawCircleV(ballPos, BALL_SIZE/2, WHITE);
        // Draw the scores
        char scoreText[32];
        sprintf(scoreText, "%d : %d", leftScore, rightScore);
        DrawText(scoreText, WINDOW_WIDTH/2 - MeasureText(scoreText, FONTSIZE)/2, 30, FONTSIZE, WHITE);

        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}

