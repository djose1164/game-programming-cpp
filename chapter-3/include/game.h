/**
 * @file game.h
 * @author Daniel Victoriano (@djose1164)
 * @brief
 * @version 0.1
 * @date 2022-08-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

class Actor;           /* Forward declaration. */
class SpriteComponent; /* Forward declaration. */
class Asteroid;        /* Forward declaration. */
class Actor;           /* Forward declaration. */

/**
 * @brief Encapsulate the playable area, that is, the screen. As well, this class
 * handle the several actors and components in game.
 *
 */
class Game
{
public:
    Game();

    /**
     * @brief Initialize the game. Call this always after instantiation.
     * 
     * @return true If initialization was successful.
     * @return false If initialization failed.
     */
    bool initialize();

    /**
     * @brief Run the game loop while running is true.
     *
     */
    void run_loop();

    /**
     * @brief Close the game & release any occupied memory.
     *
     */
    void shutdown();

    /**
     * @brief Add actor to this game.
     * @details The actor has to be previous added to be updated and drew.
     *
     * @param actor Actor to add.
     */
    void add_actor(Actor *actor);

    /**
     * @brief Remove an existing actor from this game.
     *
     * @param actor Actor to remove. Is safe passing null.
     */
    void remove_actor(Actor *actor);

    void add_sprite(SpriteComponent *sprite);
    void remove_sprite(SpriteComponent *sprite);

    SDL_Texture *get_texture(const std::string &filename);

    void add_asteroid(Asteroid *asteroid);
    void remove_asteroid(Asteroid *asteroid);

    unsigned screen_width() const;
    unsigned screen_height() const;

private:
    void process_input();
    void update();
    void render();
    void load_data();
    void unload_data();

    const unsigned screen_width_;
    const unsigned screen_height_;

    std::unordered_map<std::string, SDL_Texture *> textures_;

    std::vector<Actor *> actors_;
    std::vector<Actor *> pending_actors_;
    std::vector<SpriteComponent *> sprites_;

    SDL_Window *window_;
    SDL_Renderer *renderer_;
    Uint64 ticks_count_;

    bool running_;
    bool updating_actors_;

    class Ship *ship_;
    std::vector<Asteroid *> asteroids_;
};

#endif // GAME_H
