#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>

struct Vector2
{
    float x;
    float y;
};

struct Ball
{
    Vector2 position;
    Vector2 velocity;
};

class Game
{
public:
    Game();

    bool initialize();

    void run_loop();

    void shutdown();

private:
    void process_input();

    void update_game();

    void generate_output();

    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 ticks_count;

    bool is_running; // Game should continue to run.

    int paddle_dir; // Direction of paddle.
    int second_paddle_dir;

    std::vector<Ball> balls;
    
    Vector2 paddle_pos;
    Vector2 second_paddle_pos;
};

#endif // GAME_H
