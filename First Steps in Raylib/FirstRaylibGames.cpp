#include <raylib.h>

int main() 
{
    // declaração de variáveis para facilitar as coisas, usados para parametros de posição da bolinha
    int ballX = 400; 
    int ballY = 400;

    // Criando uma "Color" com base no sistema RGBA
    Color green = {20, 160, 133, 255};

    // Função que desenha a tela do app (dimensão X, dimensãi Y, nome da janela) - as dimensões são medidas em Pixel
    InitWindow(800, 800, "My first raylib game");
    SetTargetFPS(60); // configura para fazer o gameloop 60x por segundo (num mundo ideial)

    // Game Loop
    while(WindowShouldClose() == false)
    {
        // 1. Event Handling

        // mapeamento de movimentação da bolinha
        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            ballX += 3;
        } else if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            ballX -= 3;
        } else if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            // no caso, quanto maior o valor de "Y" mais baixo está no plano da janela.
            // o ponto 0,0 das coordenadas é o canto superior esquerdo do munitor.
            // conforme o valor de Y aumenta, as coisas descem.
            ballY -= 3;
        } else if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            ballY += 3;
        }

        // 2. Updating Positions

        // 3. Drawing
        BeginDrawing();
        ClearBackground(green);  // Limpa a tela a cada frame
        DrawCircle(ballX, ballY, 20, WHITE); // Desenha a bolinha a cada frame

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
