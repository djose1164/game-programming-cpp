#include "game.h"
#include "sprite_component.h"
#include "ship.h"
#include "bg_sprite_component.h"

#include <algorithm>
#include <SDL2/SDL_image.h>

constexpr unsigned screen_width = 1024;
constexpr unsigned screen_height = 768;

Game::Game()
    : window{nullptr}, renderer{nullptr}, running_{true}, updating_actors{false}
{
}

bool Game::initialize()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "Game Programming in C++ -Chapter 2-",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width,
        screen_height,
        0);

    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        SDL_Log("Failed to create renderer");
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    load_data();
    ticks_count = SDL_GetTicks64();
    return true;
}

void Game::run_loop()
{
    while (running())
    {
        process_input();
        update();
        render();
    }
}

bool Game::running() const
{
    return running_;
}

void Game::process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running_ = false;
            break;
        }
    }

    const auto state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE])
        running_ = false;
    
    ship_->process_keyboard(state);
}

void Game::update()
{
    const auto timeout = SDL_GetTicks64() + 16;
    while (SDL_GetTicks64() < timeout)
        ;

    auto delta_time = (SDL_GetTicks64() - ticks_count) / 1000.f;
    if (delta_time > .05f)
        delta_time = .05f;
    ticks_count = SDL_GetTicks64();

    // Update all actors
    updating_actors = true;
    for (auto actor : actors)
        actor->update(delta_time);
    updating_actors = false;

    // Move any pending actor to actors
    for (auto pending : pending_actors)
        actors.emplace_back(pending);
    pending_actors.clear();

    std::vector<Actor *> dead_actors;
    for (auto actor : actors)
        if (actor->state() == Actor::State::DEAD)
            dead_actors.emplace_back(actor);

    // Delete dead actors (which removes them from actors)
    for (auto actor : dead_actors)
        delete actor;
}

void Game::render()
{
    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        0,
        255);
    SDL_RenderClear(renderer);

    for (auto sprite : sprites)
        sprite->draw(renderer);

    SDL_RenderPresent(renderer);
}

SDL_Texture *Game::get_texture(const std::string &file_name)
{
    SDL_Texture *texture{nullptr};
    auto iter{game_textures.find(file_name)};

    if (iter != game_textures.end())
        texture = iter->second;
    else
    {
        auto surface = IMG_Load(file_name.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load texture: %s", SDL_GetError());
            return nullptr;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture)
        {
            SDL_Log("Failed to convert surface to texture for %s", file_name.c_str());
            return nullptr;
        }

        game_textures.emplace(file_name.c_str(), texture);
    }
    return texture;
}

void Game::load_data()
{
    ship_ = new Ship(this);
    ship_->position(Vector2(100.f, 384.f));
    ship_->scale(1.5f);

    // Create actor for the background
    auto tmp = new Actor(this);
    tmp->position(Vector2(512.f, 384.f));

    //  Create the far back background
    auto bg = new BGSpriteComponent(tmp);
    bg->screen_size(
        Vector2(
            static_cast<float>(screen_width),
            static_cast<float>(screen_height)));
    std::vector<SDL_Texture *> bg_textures{
        get_texture("assets/Farback01.png"),
        get_texture("assets/Farback02.png")
    };
    bg->textures(bg_textures);
    bg->scroll_speed(-100.f);

    // Create the close background
    bg = new BGSpriteComponent(tmp, 50);
    bg->screen_size(
        Vector2(
            static_cast<float>(screen_width),
            static_cast<float>(screen_height)));

    bg_textures = {
        get_texture("assets/Stars.png"),
        get_texture("assets/Stars.png")};

    bg->textures(bg_textures);
    bg->scroll_speed(-200.f);
}

void Game::unload_data()
{
    while (!actors.empty())
        delete actors.back();

    for (auto i : game_textures)
        SDL_DestroyTexture(i.second);
    game_textures.clear();
}

void Game::add_actor(Actor *actor)
{
    // If updating actors, needs to add to pending
    if (updating_actors)
        pending_actors.emplace_back(actor);
    else
        actors.emplace_back(actor);
}

void Game::remove_actor(Actor *actor)
{
    auto iter = std::find(pending_actors.begin(), pending_actors.end(), actor);
    if (iter != pending_actors.end())
    {
        // Swap to end of vector & pop off (avoid erase copies)
        std::iter_swap(iter, pending_actors.end() - 1);
        pending_actors.pop_back();
    }

    iter = std::find(actors.begin(), actors.end(), actor);
    if (iter != actors.end())
    {
        std::iter_swap(iter, actors.end() - 1);
        actors.pop_back();
    }
}

void Game::add_sprite(SpriteComponent *sprite)
{
    auto my_draw_order = sprite->draw_order();
    auto iter{sprites.begin()};

    // Find the insertion point (the first element with higher order than me)
    for (; iter != sprites.end(); ++iter)
        if (my_draw_order < (*iter)->draw_order())
            break;

    // Inserts element before position of iter
    sprites.insert(iter, sprite);
}

void Game::remove_sprite(SpriteComponent *sprite)
{
    auto iter{std::find(sprites.begin(), sprites.end(), sprite)};
    if (iter != sprites.end())
        sprites.erase(iter);
}

void Game::shutdown()
{
    unload_data();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}