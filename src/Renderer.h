#pragma once
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

const int WINDOW_W = 640;
const int WINDOW_H = 480;

class Renderer
{

public:
    Renderer(SDL_Window *window);

    void render();
    void clear();
    void delay(int time);

    void setBackgroundTransparent();
    void color(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);

    void line(int x1, int y1, int x2, int y2);
    void AAline(int x1, int y1, int x2, int y2);
    void rectangle(int x, int y, int w, int h);
    void drawCube(std::vector<glm::vec2> const &screenPoints);

private:
    SDL_Renderer *renderer;
};