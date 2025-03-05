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

#define LIGHT_SOURCE_X 200
#define LIGHT_SOURCE_Y 280
#define LIGHT_SOURCE_R 40

#define OBJECT_X 500
#define OBJECT_Y 280
#define OBJECT_R 80
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
struct Circle lightbulb = {LIGHT_SOURCE_X, LIGHT_SOURCE_Y, LIGHT_SOURCE_R};
double lightbulb_radius_squared; // setting this as a global so i dont have to recalculate every frame
struct Circle object = {OBJECT_X, OBJECT_Y, OBJECT_R};
double object_radius_squared; // same as before
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
    // draw the object that casts shadows
    draw_circle(object, 100, 100, 100, 255);
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
            // check if we are on the lightbulb or the object or neither
            double distance_to_lightbulb = pow(x - lightbulb.x, 2) + pow(y - lightbulb.y, 2);
            if (distance_to_lightbulb <= lightbulb_radius_squared)
            {
                lightbulb.x = x;
                lightbulb.y = y;
            }
            double distance_to_object = pow(x - object.x, 2) + pow(y - object.y, 2);
            if (distance_to_object <= lightbulb_radius_squared)
            {
                object.x = x;
                object.y = y;
            }
        }
    }
    return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    lightbulb_radius_squared = pow(lightbulb.radius, 2);
    object_radius_squared = pow(object.radius, 2);
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
