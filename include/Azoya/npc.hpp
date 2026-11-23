#ifndef AZOYA_NPC_HPP
#define AZOYA_NPC_HPP

#include <Azoya/dialog/dialog_box.hpp>
#include <Azoya/dialog/input_box.hpp>
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
    void Click(sf::Vector2f mouse_pos);

    Node_mode Get_mode() {return dialog_graf[ current_dialog_node_id ].node_mode;}

    static Npc_parser parser;

    Dialog_box dialog_box{};
    Input_box input_box{};

    sf::Texture dialog_texture{};
    sf::Sprite dialog_sprite{dialog_texture};

    static sf::Texture world_texture;
    sf::Sprite world_sprite{world_texture};

private:
    std::string_view Node_mode_to_string(Node_mode mode);

    std::vector <Dialog_node> dialog_graf{};

    uint32_t current_dialog_node_id{};

    uint32_t input_nodes_offset{};

    Texture_changer tex_changer{};

    sf::Font font;

    friend class Npc_parser;
};

}

#endif // AZOYA_NPC_HPP
