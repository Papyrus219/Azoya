#ifndef AZOYA_NPC_HPP
#define AZOYA_NPC_HPP

#include <Azoya/dialog/dialog_box.hpp>
#include <Azoya/texture_changer.hpp>
#include <Azoya/dialog/dialog_node.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

namespace azoya
{

class Npc_parser;

class Npc
{
public:


private:
    std::vector <Dialog_node> dialog_graf{};

    static Npc_parser parser;

    uint32_t current_dialog_node_id{};

    sf::Texture texture{};
    sf::Sprite sprite{texture};
    Texture_changer tex_changer{};
    Dialog_box dialog_box{};

    friend class Npc_parser;
};

}

#endif // AZOYA_NPC_HPP
