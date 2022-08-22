#include "game.h"

constexpr unsigned thickness{15};
constexpr double paddle_height{100.};
constexpr unsigned screen_width{1024};
constexpr unsigned screen_height{768};

Game::Game()
    : window{nullptr}, renderer{nullptr}, ticks_count{}, is_running{true}, paddle_dir{}
{
}

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
        screen_width,
        screen_height,
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
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) // if renderer creation fails
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }
    Ball ball1, ball2;
    balls.push_back(ball1);
    balls.push_back(ball2);
    for (auto &ball : balls)
    {
        ball.position.x = screen_width / 2.f;
        ball.position.y = screen_height / 2.f;
        ball.velocity.y = 235.f;
    }
    balls[0].velocity.x = -200.f;
    balls[1].velocity.x = 200.f;

    paddle_pos.x = 10.f;
    paddle_pos.y = screen_height / 2.f;

    second_paddle_pos.x = screen_width - 25.f;
    second_paddle_pos.y = screen_height / 2.f;

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

    while (SDL_PollEvent(&event))
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

    second_paddle_dir = 0;
    if (state[SDL_SCANCODE_I])
        --second_paddle_dir;
    if (state[SDL_SCANCODE_K])
        ++second_paddle_dir;
}

void Game::update_game()
{
    const auto timeout = SDL_GetTicks64() + 16;
    while (SDL_GetTicks64() < timeout)
        ;

    auto delta_time = (SDL_GetTicks64() - ticks_count) / 1000.f;
    ticks_count = SDL_GetTicks64();

    if (delta_time > .05f) // Clamp delta time value
        delta_time = .05f;

    // Set upper and lower bound to paddle
    if (paddle_dir) // if non-zero
    {
        paddle_pos.y += paddle_dir * 300.f * delta_time;

        if (paddle_pos.y < (paddle_height / 2.f + thickness))
            paddle_pos.y = paddle_height / 2.f + thickness;
        else if (paddle_pos.y > screen_height - paddle_height / 2.f - thickness)
            paddle_pos.y = screen_height - paddle_height / 2.f - thickness;
    }

    // Set upper and lower bound to paddle
    if (second_paddle_dir) // if non-zero
    {
        second_paddle_pos.y += second_paddle_dir * 300.f * delta_time;
        if (second_paddle_pos.y < paddle_height / 2.f + thickness)
            second_paddle_pos.y = paddle_height / 2.f + thickness;
        else if (second_paddle_pos.y > screen_height - (paddle_height / 2.f - thickness))
            second_paddle_pos.y = screen_height - paddle_height / 2.f - thickness;
    }

    for (auto &ball : balls)
    {
        ball.position.x += ball.velocity.x * delta_time;
        ball.position.y += ball.velocity.y * delta_time;

        // Collision with top wall
        if (ball.position.y <= thickness && ball.velocity.y < 0.f)
            ball.velocity.y *= -1;
        // Collision with bottom wall
        if (ball.position.y > 768 - thickness && ball.velocity.y > 0.f)
            ball.velocity.y *= -1;

        // Collision with right wall
        /*if (ball_pos.x > 1024 - thickness && ball_pos.y > 0.f)
            ball_vel.x *= -1;*/

        auto diff = ball.position.y - paddle_pos.y;
        diff = diff > 0.f ? diff : -diff;

        if (
            diff <= paddle_height / 2.f &&                        // our y-difference is small enough and
            ball.position.x >= 20.f && ball.position.x <= 25.f && // ball is at correct x-position
            ball.velocity.x < 0.f                                 // the ball is moving to the left
        )
            ball.velocity.x *= -1;
        // Second paddle collation
        diff = ball.position.y - second_paddle_pos.y;
        diff = diff ? diff : -diff;
        if (
            diff <= paddle_height / 2.f &&
            ball.position.x >= screen_width - 30.f && ball.position.x <= screen_width - 25.f &&
            ball.velocity.x > 0.f)
            ball.velocity.x *= -1;

        if (ball.position.x < 0.f)
            is_running = false;
        else if (ball.position.x > screen_width)
            is_running = false;
    }
}

void Game::generate_output()
{
    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        255,
        255);

    // Clear back buffer
    SDL_RenderClear(renderer);

    // Draw walls
    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255);
    SDL_Rect wall{
        0,
        0,
        1024,
        thickness};
    SDL_RenderFillRect(renderer, &wall);

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255);

    // Draw bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect(renderer, &wall);

    // Left paddle
    SDL_Rect paddle{
        static_cast<int>(paddle_pos.x),
        static_cast<int>(paddle_pos.y - paddle_height / 2),
        thickness,
        static_cast<int>(paddle_height)};
    SDL_RenderFillRect(renderer, &paddle);

    // Right paddle
    SDL_Rect second_paddle{
        static_cast<int>(second_paddle_pos.x),
        static_cast<int>(second_paddle_pos.y - paddle_height / 2),
        thickness,
        static_cast<int>(paddle_height)};
    SDL_RenderFillRect(renderer, &second_paddle);
    for (auto &ball : balls)
    {
        SDL_Rect ball_{
            static_cast<int>(ball.position.x - thickness / 2),
            static_cast<int>(ball.position.y - thickness / 2),
            thickness,
            thickness};
        SDL_RenderFillRect(renderer, &ball_);
    }
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