#include <Renderer.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Cube.h>

void handleInput(bool &quit, float &angle, bool &isOrthographic)
{
    const float ANGLE_INCREMENT = 5.0f;

    // Event loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            // Handle keydown event
            if (event.key.keysym.sym == SDLK_q)
            {
                // Handle Q key press
                std::cout<<"Q key pressed\n";
                angle -= ANGLE_INCREMENT;
            }
            else if (event.key.keysym.sym == SDLK_e)
            {
                // Handle E key press
                std::cout<<"E key pressed\n";
                angle += ANGLE_INCREMENT;
            }
            else if (event.key.keysym.sym == SDLK_z)
            {
                // Handle Z key press
                std::cout<<"Z key pressed\n";
            }
            else if (event.key.keysym.sym == SDLK_c)
            {
                // Handle C key press
                std::cout<<"C key pressed\n";
            }
            else if (event.key.keysym.sym == SDLK_o)
            {
                // Handle O key press
                std::cout<<"O key pressed\n";
                isOrthographic = !isOrthographic;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            // Handle keyup event
        }
    }
}

int main(int argc, char *argv[])
{
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    SDL_Window *window = SDL_CreateWindow("My SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);

    Renderer renderer(window);

    // Main loop
    bool quit = false;
    float angle = 30.0f;
    bool isOrthographic = false;
    while (!quit)
    {
        handleInput(quit, angle, isOrthographic);

        // black background
        renderer.color(0, 0, 0);
        renderer.clear();

        // draw a white line
        renderer.color(255, 255, 255);

        std::vector<glm::vec2> points = generateCube(angle, isOrthographic);
        renderer.drawCube(points);

        renderer.render();
        renderer.delay(16);
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
