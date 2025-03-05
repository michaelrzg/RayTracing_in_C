// raytracing in C
// Michael Rizig
// Using new SDL3 lib released Jan 2025

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
// create window and renderer (from SDL docs)
SDL_Window *window;
SDL_Renderer *renderer;
// track if mouse is draggin and current drag location
bool isDragging = false;
int dragStartX, dragStartY;

// struct of a circle
struct Circle
{
    double x;
    double y;
    double radius;
};
// create the primary circle on the screen
struct Circle lightbulb = {100, 100, 40};

// this function draws a passed circle on the screen
void draw_circle(struct Circle circle, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a); // Set the draw color to white
    double radius_squared = pow(circle.radius, 2);
    for (double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++)
    {
        for (double y = circle.y - circle.radius; y < circle.y + circle.radius; y++)
        {
            if (x >= circle.x - circle.radius)
            {
                double distance_to_center = pow(x - circle.x, 2) + pow(y - circle.y, 2);
                if (distance_to_center <= radius_squared)
                {
                    SDL_FRect pixel = {x, y, 1.0f, 1.0f};
                    SDL_RenderFillRect(renderer, &pixel);
                }
            }
        }
    }
}

// this function frees up memory by deconstructing objects on quit
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void render()
{
    // set background color here
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // draw light sorce (struct Circle)
    draw_circle(lightbulb, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_Delay(10);
    render();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            isDragging = true;
            dragStartX = event->button.x;
            dragStartY = event->button.y;
        }
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            isDragging = false;
        }
    }

    if (event->type == SDL_EVENT_MOUSE_MOTION)
    {
        if (isDragging)
        {
            int x = event->motion.x;
            int y = event->motion.y;
            SDL_Log("Dragging: x=%d, y=%d", x, y);

            lightbulb.x = x;
            lightbulb.y = y;
        }
    }
    return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    // check initilization
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error Initilizing");
        return SDL_APP_FAILURE;
    }

    // create window
    window = SDL_CreateWindow("Raytracing", WIDTH, HEIGHT, 0);
    // check if window was created
    if (!window)
    {
        SDL_Log("Error creating window");
        return SDL_APP_FAILURE;
    }

    // create renderer
    renderer = SDL_CreateRenderer(window, NULL);
    // check if renderer was created
    if (!renderer)
    {
        SDL_Log("Error creating renderer");
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}
