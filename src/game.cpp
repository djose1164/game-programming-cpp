#include "game.h"

constexpr unsigned thickness{15};
constexpr double paddleH{100.};

Game::Game()
    : window{nullptr}
    , renderer{nullptr}
    , ticks_count{}
    , is_running{true}
    , paddle_dir{}
{}

bool Game::initialize()
{
    auto result = SDL_Init(SDL_INIT_VIDEO);
    if (result != 0) // if sdl initialization fails
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "Game programming in C++", // title
        100,
        50,
        1024,
        768,
        0 // flags, 0 for none
    );

    
    if (!window) // if window creation fails
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) // if renderer creation fails
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    ball_pos.x = 1024.f/2.f;
    ball_pos.y = 768.f/2.f;

    paddle_pos.x = 10.f;
    paddle_pos.y = 768.f/2.f;

    ball_vel.x = -200.f;
    ball_vel.y = 235.f;

    return true;
}


void Game::run_loop()
{
    while (is_running)
    {
        process_input();
        update_game();
        generate_output();
    }
}

void Game::process_input()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            is_running = false;
            break;
        }
    }

    const auto state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE])
        is_running = false;
    
    // Update paddle direction based on w/s keys.
    paddle_dir = 0;
    if (state[SDL_SCANCODE_W])
        paddle_dir -= 1;
    if (state[SDL_SCANCODE_S])
        paddle_dir += 1;
}

void Game::update_game()
{
    const auto timeout = SDL_GetTicks64() + 16;
    while (SDL_GetTicks64() < timeout)
        ;
    
    auto delta_time = (SDL_GetTicks64() - ticks_count)/1000.f;
    ticks_count = SDL_GetTicks64();


    if (delta_time > .05f) // Clamp delta time value
        delta_time = .05f;

    if (paddle_dir)
    {
        paddle_pos.y += paddle_dir * 300.f * delta_time;
    
        if (paddle_pos.y < (paddleH/2.f + thickness))
            paddle_pos.y = paddleH/2.f + thickness;
        else if (paddle_pos.y > 768.f - paddleH/2.f - thickness)
            paddle_pos.y = 768.f - paddleH/2.f - thickness;
    }

    ball_pos.x += ball_vel.x * delta_time;
    ball_pos.y += ball_vel.y * delta_time;

    // Collision with top wall
    if (ball_pos.y <= thickness && ball_vel.y < 0.f)
        ball_vel.y *= -1;
    //Collision with bottom wall
    if (ball_pos.y > 768 - thickness && ball_vel.y > 0.f)
        ball_vel.y *= -1;
    // Collision with right wall
    if (ball_pos.x > 1024 - thickness && ball_pos.y > 0.f)
        ball_vel.x *= -1;

    auto diff = ball_pos.y - paddle_pos.y;
    diff = diff > 0.f ? diff : -diff;

    if (
        diff <= paddleH/2.f && // our y-difference is small enough and
        ball_pos.x >= 20.f && ball_pos.x <= 25.f && // ball is at correct x-position
        ball_vel.x < 0.f // the ball is moving to the left
    )
        ball_vel.x *= -1;
    
    if (ball_pos.x < 0.f)
        is_running = false;
}

void Game::generate_output()
{
    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        255,
        255
    );

    // Clear back buffer
    SDL_RenderClear(renderer);

    // Draw walls
    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255
    );
    SDL_Rect wall{
        0,
        0,
        1024,
        thickness
    };
    SDL_RenderFillRect(renderer, &wall);

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255
    );

    // Draw bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect(renderer, &wall);

    // Draw right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(renderer, &wall);

    SDL_Rect paddle{
        static_cast<int>(paddle_pos.x),
        static_cast<int>(paddle_pos.y - paddleH/2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(renderer, &paddle);

    SDL_Rect ball{
        static_cast<int>(ball_pos.x - thickness/2),
        static_cast<int>(ball_pos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(renderer, &ball);
    // Swap back buffer and front buffer
    SDL_RenderPresent(renderer);
}

void Game::shutdown()
{
    // Delete renderer before window to **avoid stack smashing**
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
}