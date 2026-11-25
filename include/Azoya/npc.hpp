#ifndef AZOYA_NPC_HPP
#define AZOYA_NPC_HPP

#include <Azoya/dialogs.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

namespace azoya
{

class Npc_parser;

class Npc
{
public:
    static Npc_parser parser;

    std::optional<Dialog_manager> dialog_manager;

    static sf::Texture world_texture;
    sf::Sprite world_sprite{world_texture};

private:
    friend class Npc_parser;
};

}

#endif // AZOYA_NPC_HPP
