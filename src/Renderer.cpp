#include "Renderer.h"

Renderer::Renderer(SDL_Window *window)
{
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Renderer::color(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::clear()
{
    SDL_RenderClear(renderer);
}

void Renderer::AAline(int x1, int y1, int x2, int y2)
{
    // Xiaolin Wu's line algorithm
    float dx = x2 - x1;
    float dy = y2 - y1;
    float gradient = dy / dx;
    if (dx == 0.0)
    {
        gradient = 1.0;
    }
    float xend = round(x1);
    float yend = y1 + gradient * (xend - x1);
    float xgap = 1.0 - fmod(x1 + 0.5, 1.0);
    int xpxl1 = xend;
    int ypxl1 = floor(yend);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 * (1.0 - fmod(yend, 1.0)));
    SDL_RenderDrawPoint(renderer, xpxl1, ypxl1);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 * fmod(yend, 1.0));
    SDL_RenderDrawPoint(renderer, xpxl1, ypxl1 + 1);
    float intery = yend + gradient;
    xend = round(x2);
    yend = y2 + gradient * (xend - x2);
    xgap = fmod(x2 + 0.5, 1.0);
    int xpxl2 = xend;
    int ypxl2 = floor(yend);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 * (1.0 - fmod(yend, 1.0)));
    SDL_RenderDrawPoint(renderer, xpxl2, ypxl2);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 * fmod(yend, 1.0));
    SDL_RenderDrawPoint(renderer, xpxl2, ypxl2 + 1);
    for (int x = xpxl1 + 1; x < xpxl2; x++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 * (1.0 - fmod(intery, 1.0)));
        SDL_RenderDrawPoint(renderer, x, floor(intery));
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 * fmod(intery, 1.0));
        SDL_RenderDrawPoint(renderer, x, floor(intery) + 1);
        intery += gradient;
    }
    // // Bresenham's line algorithm
    // const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    // if (steep)
    // {
    //     std::swap(x1, y1);
    //     std::swap(x2, y2);
    // }

    // if (x1 > x2)
    // {
    //     std::swap(x1, x2);
    //     std::swap(y1, y2);
    // }

    // const float dx = x2 - x1;
    // const float dy = fabs(y2 - y1);

    // float error = dx / 2.0f;
    // const int ystep = (y1 < y2) ? 1 : -1;
    // int y = (int)y1;

    // const int maxX = (int)x2;

    // for (int x = (int)x1; x < maxX; x++)
    // {
    //     if (steep)
    //     {
    //         SDL_RenderDrawPoint(renderer, y, x);
    //     }
    //     else
    //     {
    //         SDL_RenderDrawPoint(renderer, x, y);
    //     }

    //     error -= dy;
    //     if (error < 0)
    //     {
    //         y += ystep;
    //         error += dx;
    //     }
    // }
}

void Renderer::line(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Renderer::rectangle(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::render()
{
    SDL_RenderPresent(renderer);
}

void Renderer::setBackgroundTransparent()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Renderer::drawCube(std::vector<glm::vec2> const &screenPoints)
{
    const std::vector<glm::vec2> edges{
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},

        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},

        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},
    };

    const std::vector<glm::vec3> colors{
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 0},
        {255, 0, 255},
        {0, 255, 255},
        {255, 255, 255},
        {45, 45, 45},
    };

    // draw the box
    for (auto edge : edges)
    {
        const int x1 = screenPoints[edge.x].x;
        const int y1 = screenPoints[edge.x].y;
        const int x2 = screenPoints[edge.y].x;
        const int y2 = screenPoints[edge.y].y;
        this->line(x1, y1, x2, y2);
    }

    // draw the vertices
    const int radius = 4;
    for (int i = 0; i < screenPoints.size(); i++)
    {
        auto color = colors[i];
        this->color(color.r, color.g, color.b);

        const auto point = screenPoints[i];
        const int x = point.x;
        const int y = point.y;
        this->rectangle(x - radius, y - radius, 2 * radius, 2 * radius);
    }
}

void Renderer::delay(int time)
{
    SDL_Delay(time);
}