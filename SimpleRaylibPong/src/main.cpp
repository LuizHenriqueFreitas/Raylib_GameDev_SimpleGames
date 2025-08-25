#include <iostream>
#include <raylib.h>

using namespace std;

//criando as cores personalisadas usadas durante o projeto
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Ligth_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

//declarando as variáveis do placar
int player_score = 0;
int cpu_score = 0;

//criando a classe da bola
class Ball{
public:
    float x, y; //posição da bola no canvas
    int speed_x, speed_y; //velocidade da bola de acordo com cada eixo
    int radius; //diâmetro da bola

    void Draw() //função que desenha a bola
    {
        DrawCircle(x, y, radius, Yellow);
    }

    void Update()
    {
        x += speed_x; //atualiza a posição da bola de acordo com a velocidade no eixo
        y += speed_y; //mesma coisa de cima

        if(y + radius >= GetScreenHeight() || y - radius <= 0) //caso a bola fosse sair verticalmente da janela ela tem a velocidade do eixo "Y" espelhada
        {
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth()) //Cpu wins
        {
            cpu_score++; //adiciona pontos ao NPC
            ResetBall(); //reseta a bola no centro
        }
        if(x - radius <= 0) //Player wins
        {
            player_score++; //adiciona pontos ao NPC
            ResetBall(); //reseta a bola no centro
        }
    }

    void ResetBall() //função para resetar a bola depois de marcar um ponto
    {
        //encontrando o centro da tela
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2; 

        //deixando a velocidade e direção da bola randomicos
        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    }
};

//criando a classe do jogador
class Paddle {
protected:
    void LimitMovement() //função para limitar o tablete dentro dos limites da janela
    {
        if(y <= 0)
        {
            y = 0;
        }
        if(y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y; //posição do tablete no plano do canvas
    float width, height; //altura e largura do tablete
    int speed; //velocidade do tablete

    void Draw() //desenha o retangulo na tela
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Update() //verifica se existe interação do usuário, caso sim, move o retangulo na vertical
    {
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();//limita os movimentos dentro da janela
    }
};

//criando a classe do NPC, que é filha da classe do player
class CpuPaddle: public Paddle{
public:
    void Update(int ball_y) //sobre escreve a classe do Update do player
    {
        // algoritmo simples de "IA" -> faz com que o centro do retangulo sempre esteja horizontalmente alinhado com o centro da bola
        if(y + height/2 > ball_y)
        {
            y = y - speed;
        }
        if(y + height/2 <= ball_y)
        {
            y = y + speed;
        }
        LimitMovement();//limita o movimento do retangulo dentro da janela
    }
};

//criando os objetos com base nas classes criadas
Ball ball;
Paddle player;
CpuPaddle cpu;

int main() 
{
    //mensagem no console (tipo um backend?)
    cout << "Starting the game" << endl;

    //definindo tamanho da janela e frequencia do gameloop
    const int screen_width = 1280;
    const int screen_heigth = 800;
    InitWindow(screen_width, screen_heigth, "My Pong Game!");
    SetTargetFPS(60);

    //iniciando o objeto Bola
    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_heigth/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    //iniciando o objeto player
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_heigth/2 - player.height/2;
    player.speed = 6;

    //inicializando o bot
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_heigth/2 - cpu.height/2;
    cpu.speed = 6;


    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        //Updating
        //atualizando os parametros dos objetos a cada frame
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //checking for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }

        //Drawing
        ClearBackground(Dark_Green); //limpa o fundo a cada frame
        DrawRectangle(screen_width/2, 0, screen_width/2, screen_heigth, Green); //pinta o lado mais claro do campo (apenas estético)
        DrawCircle(screen_width/2, screen_heigth/2, 150, Ligth_Green); //desenha o circulo central (apenas estético)
        DrawLine(screen_width / 2, 0, screen_width / 2,screen_heigth, WHITE); //desenha a linha do meio de campo
        //atualizando as posições dos objetos a cada frame
        ball.Draw();
        cpu.Draw();
        player.Draw();
        //exibição do placar em texto
        DrawText(TextFormat("%i", cpu_score), screen_width/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width/4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}