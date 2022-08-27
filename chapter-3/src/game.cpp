#include "game.h"
#include "utils/random.h"
#include "actors/actor.h"
#include "components/sprite_component.h"
#include "actors/asteroid.h"

#include <SDL2/SDL_image.h>
#include <algorithm>

Game::Game()
    : screen_width_{1024}
    , screen_height_{768}
    , window_{nullptr}
    , renderer_{nullptr}
    , running_{true}
    , updating_actors_{false}
{
    SDL_Log("Game created!");
}

bool Game::initialize()
{
    SDL_Log("Initializing game...");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) // Can init SDL
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window_ = SDL_CreateWindow(
        "Game Programming in C++ -chapter 3-",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width(),
        screen_height(),
        0
    );
    if (!window_)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer_ = SDL_CreateRenderer(
        window_,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );

    if (!IMG_Init(IMG_INIT_PNG))
    {
        SDL_Log("Uable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    Random::init();
    load_data();
    ticks_count_ = SDL_GetTicks64();
    SDL_Log("Game initialzed!");
    return true;
}

void Game::run_loop()
{
    while (running_)
    {
        process_input();
        update();
        render();
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
            running_ = false;
            break;
        }
    }

    auto key_state = SDL_GetKeyboardState(nullptr);
    if (key_state[SDL_SCANCODE_ESCAPE])
        running_ = false;
    
    updating_actors_ = true;
    for (auto actor : actors_)
        actor->proccess_input(key_state);
    updating_actors_ = false;
}

void Game::update()
{
    auto timeout = SDL_GetTicks64() + 16;
    while (SDL_GetTicks64() < timeout);

    auto delta_time = (SDL_GetTicks64() - ticks_count_)/1000.f;
    if (delta_time > .05f)
        delta_time = .05f;
    ticks_count_ = SDL_GetTicks64();

    updating_actors_ = true;
    for (auto actor : actors_)
        actor->update(delta_time);
    updating_actors_ = false;

    for (auto pending : pending_actors_)
        actors_.emplace_back(pending);
    pending_actors_.clear();

    std::vector<Actor *> dead_actors;
    for (auto actor : actors_)
        if (actor->state() == Actor::State::DEAD)
            dead_actors.emplace_back(actor);
    
    for (auto dead : dead_actors)
        delete dead;
}

void Game::render()
{
    SDL_SetRenderDrawColor(
        renderer_,
        15,
        0,
        0,
        150
    );
    SDL_RenderClear(renderer_);

    for (auto sprite : sprites_)
        sprite->draw(renderer_);
    
    SDL_RenderPresent(renderer_);
}

void Game::load_data()
{
    SDL_Log("Loading data into game...");
    constexpr size_t num_asteroid{15};
    for (size_t i{0}; i < num_asteroid; ++i)
        new Asteroid(this);
    SDL_Log("Data loaded into game!");
}

void Game::unload_data()
{
    while (!actors_.empty())
        delete actors_.back();

    for (auto texture : textures_)
        SDL_DestroyTexture(texture.second);
    textures_.clear();
}

void Game::shutdown()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void Game::add_actor(Actor *actor)
{
    if (updating_actors_)
        pending_actors_.emplace_back(actor);
    else
        actors_.emplace_back(actor);
}

void Game::remove_actor(Actor *actor)
{
    // Is it in pending actors?
    auto iter{std::find(pending_actors_.begin(), pending_actors_.end(), actor)};
    if (iter != pending_actors_.end())
    {
        std::iter_swap(iter, pending_actors_.end() - 1);
        pending_actors_.pop_back();
    }

    iter = std::find(actors_.begin(), actors_.end(), actor);
    if (iter != actors_.end())
    {
        std::iter_swap(iter, actors_.end() -1 );
        actors_.pop_back();
    }
}

void Game::add_sprite(SpriteComponent *sprite)
{
    auto my_order = sprite->update_order();
    auto iter = sprites_.begin();

    for (; iter != sprites_.end(); ++iter)
        if (my_order < (*iter)->update_order())
            break;
    
    sprites_.insert(iter, sprite);
    SDL_Log("sprites_.size(): %zu", sprites_.size());

}

void Game::remove_sprite(SpriteComponent *sprite)
{
    auto iter{std::find(sprites_.begin(), sprites_.end(), sprite)};
    sprites_.erase(iter);
}

SDL_Texture *Game::get_texture(const std::string &filename)
{
    SDL_Texture *texture{nullptr};

    //Is the texture already in the map?
    auto iter{textures_.find(filename)};
    if (iter != textures_.end())
        texture = iter->second;
    else
    {
        // Load from file.
        auto surface{IMG_Load(filename.c_str())};
        if (!surface)
        {
            SDL_Log("Failed to load texture file: %s", filename.c_str());
            return nullptr;
        }

        // Create texture from surface.
        texture = SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface); // After creating, free it.
        if (!texture)
        {
            SDL_Log("Failed to convert surface to texture for: %s", filename.c_str());
            return nullptr;
        }
        SDL_assert(texture);
        textures_.emplace(filename.c_str(), texture);
    }

    return texture;
}

void Game::add_asteroid(Asteroid *asteroid)
{
    asteroids_.emplace_back(asteroid);
    SDL_Log("asteroids_.size(): %zu", asteroids_.size());

}

void Game::remove_asteroid(Asteroid *asteroid)
{
    auto iter{std::find(
        asteroids_.begin(),
        asteroids_.end(),
        asteroid
    )};
    if (iter != asteroids_.end())
        asteroids_.erase(iter);
}

unsigned Game::screen_width() const
{
    return screen_width_;
}

unsigned Game::screen_height() const
{
    return screen_height_;
}
