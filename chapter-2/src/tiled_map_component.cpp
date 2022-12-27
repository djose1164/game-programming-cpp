#include "tiled_map_component.h"


#include <ios>
#include <fstream>
#include <sstream>

auto TileMapComponent::load(const std::string &filepath)
{
    std::vector<std::string> row;

    std::string line, word;
    std::fstream file{filepath, std::ios::in};

    if (!file.is_open())
        return false;
    
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream str{line};
        while (std::getline(str, word, ','))
        {
            row.push_back(word);
            tile_map_.push_back(row);
        }
    }
    return true;
}

void TileMapComponent::draw(SDL_Renderer *renderer)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 32;
    src.h = 32;

    SDL_Rect dst;
    

    SDL_RenderCopy();
}