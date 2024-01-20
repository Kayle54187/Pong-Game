//
// Created by kayle on 1/20/24.
//

#include <iostream>
#include <raylib.h>

using namespace std;

int playerScore = 0;
int cpuScore = 0;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        //Drawing the circle
        DrawCircle(x, y, radius, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) {
            cpuScore++;
            speed_x *= -1;
        }
        if (x - radius <= 0) {
            speed_x *= -1;
            playerScore++;
        }
    }
};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    };

public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        //left
        DrawRectangle(x, y, 20, 120, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
        LimitMovement();
    }
};

class CpuPadle : public Paddle {
public:
    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y) {
            y = y + speed;
        }
        LimitMovement();
    }
};

Ball ball;
Paddle player;
CpuPadle cpuPaddle;

int main() {

    cout << "Game Stating..." << endl;

    const int screenWidth = 1280;
    const int screenHeight = 800;

    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.radius = 20;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;

    cpuPaddle.width = 25;
    cpuPaddle.height = 120;
    cpuPaddle.x = 5;
    cpuPaddle.y = screenHeight / 2 - cpuPaddle.height / 2;
    cpuPaddle.speed = 6;


    InitWindow(screenWidth, screenHeight, "Pong Game By KVS");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ball.Update();
        player.Update();
        cpuPaddle.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                    Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                    Rectangle{cpuPaddle.x, cpuPaddle.y, cpuPaddle.width, cpuPaddle.height})) {
            ball.speed_x *= -1;
        }

        ClearBackground(BLACK);
        //Drawing Separating Line
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.Draw();
        player.Draw();
        cpuPaddle.Draw();

        DrawText(TextFormat("CPU Score: %i", cpuScore), screenWidth / 4 - 20, 20, 20, WHITE);
        DrawText(TextFormat("Player Score: %i", playerScore), 3 * screenWidth / 4 - 20, 20, 20, WHITE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}