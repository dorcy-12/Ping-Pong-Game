#include <iostream>
#include <raylib.h>
#include <string>


using namespace std;


int cpuScore= 0;
int playerScore = 0;

class Ball {
public:
    int radius;
    float x,y;
    int speedX{}, speedY{};
    void Draw() {
        DrawCircle(x,y,radius, ORANGE);
    }
    void Move() {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius  <= 0) {
           speedY = -speedY;
        }
        else if (x + radius >= GetScreenWidth()) { // player wins a point
            playerScore++;
            ResetBall();
        }else if( x - radius <= 0) {
            cpuScore++;
            ResetBall();
        }
    }
    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speed_choices[2]= {-1,1};
        speedX *= speed_choices[GetRandomValue(0,1)];
        speedY *= speed_choices[GetRandomValue(0,1)];
    }
};

class Paddle {
    public:
    float width = 15, height= 70;
    float x,y;
    int speed = 6;
    float buffer = 10; // buffer space for paddles on y-axis
    Paddle(float x, float y) {
        this->x = x;
        this->y = y;
    }


    void Draw() {
        DrawRectangle(x,y, width, height,WHITE);
    }
    void Update() {
        if (IsKeyDown(KEY_UP) && y - buffer > 0) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN) && y + buffer + height < GetScreenHeight() ) {
            y += speed;
        }
    }
};

class botPaddle: public Paddle {
public:
    botPaddle(float x , float y): Paddle(x, y) {
    }
    void Update(int ball_y) {
        if(y + height/2 < ball_y) {
            y += speed;
        }
        else if(y + height/2 > ball_y) {
            y -= speed;
        }
    }

};
int main() {
    constexpr int screenHeight= 600;
    constexpr int screenWidth = 800;
    Ball ball;

    ball.radius = 10;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2;
    ball.speedX = 7;
    ball.speedY = 7;

    Paddle player(0, (screenHeight/ 2.0)-30);
    botPaddle cpu(screenWidth-20, (screenHeight/ 2.0)-30);

    InitWindow(screenWidth,screenHeight,"Ball game");
    SetTargetFPS(60);

    constexpr Color bgColor = {20,160,133,255};
    constexpr Color midColor = {99,232,200,255};

    while (!WindowShouldClose()) {

        //Drawing

        BeginDrawing();



        //1. collision detection


        //2. Winning

        ClearBackground(bgColor);

        DrawCircle(400,300,60,midColor);
        DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,WHITE);

        if (cpuScore == 5) {
            DrawText("YOU LOSE :(", screenWidth/3, screenHeight/2, 50, WHITE);
        }
        else if (playerScore == 5) {
            DrawText("YOU WIN ;)", screenWidth/3, screenHeight/2, 50, WHITE);
        }
        else {
            ball.Move();
            player.Update();
            cpu.Update(ball.y);

            if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius,Rectangle{player.x,player.y,player.width,player.height})) {
                ball.speedX *= -1;

            }else if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.height})) {
                ball.speedX *= -1;
            }

            player.Draw();
            cpu.Draw();
            ball.Draw();

        }

        DrawText(to_string(playerScore).c_str(), screenWidth/4, 20, 50, WHITE);
        DrawText(to_string(cpuScore).c_str(), (screenWidth*3)/4, 20, 50, WHITE);
        EndDrawing();
    }
    return 0;
}
