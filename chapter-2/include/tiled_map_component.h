#ifndef TILED_MAP_COMPONENT_H
#define TILED_MAP_COMPONENT_H

#include "sprite_component.h"

#include <string>
#include <vector>

class TileMapComponent : public SpriteComponent
{
    auto load(const std::string &filepath);
    auto read();
    
    void draw(SDL_Renderer *renderer) override;

private:
    std::vector<std::vector<std::string>> tile_map_;
};

#endif //TILED_MAP_COMPONENT_H
