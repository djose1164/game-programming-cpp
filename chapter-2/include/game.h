#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

class Game
{
public:
    Game();

    /**
     * @brief Initialize game status and vars.
     *
     * @return true Initialization success.
     * @return false Initialization failed.
     */
    bool initialize();

    /**
     * @brief Mainloop running as long as `is_running` is true.
     *
     */
    void run_loop();

    bool running() const;

    /**
     * @brief Close window & clean up.
     *
     */
    void shutdown();

    /**
     * @brief Add actor to this game.
     *
     * @param actor Actor to be added.
     */
    void add_actor(class Actor *actor);

    /**
     * @brief Remove an existing actor from this game.
     *
     * @param actor Existing actor to be deleted.
     */
    void remove_actor(class Actor *actor);

    /**
     * @brief Load texture from file.
     *
     * @param file_name Path to file.
     * @return SDL_Texture* On success pointer to texture, otherwise nullptr.
     */
    SDL_Texture *get_texture(const std::string &file_name);

    void add_sprite(class SpriteComponent *sprite);

    void remove_sprite(class SpriteComponent *sprite);

private:
    void process_input();

    void update();

    void render();

    void load_data();

    void unload_data();

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running_;
    bool updating_actors;

    Uint64 ticks_count;

    std::vector<class Actor *> actors;
    std::vector<class Actor *> pending_actors;

    // All the sprite components drawn.
    std::vector<class SpriteComponent *> sprites;

    std::unordered_map<std::string, SDL_Texture *> game_textures;

    class Ship *ship_;
};

#endif // GAME_H
