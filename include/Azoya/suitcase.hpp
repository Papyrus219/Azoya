#ifndef AZOYA_SUITCASE_HPP
#define AZOYA_SUITCASE_HPP

#include <Azoya/dialogs.hpp>
#include <Azoya/texture_changer.hpp>

namespace azoya
{

class Suitcase
{
public:
    void Init(const std::filesystem::path & path);

    void Click(sf::Vector2f mouse_pos);

    Node_mode Get_mode() {return dialog_graf[ current_dialog_node_id ].node_mode;}

    Dialog_parser dialog_parser{};

    Dialog_box dialog_box{};
    Input_box input_box{};
    sf::Texture suitcase_texture{};
    sf::Sprite suitcase_sprite{suitcase_texture};

    sf::Texture items_texture{};
    sf::Sprite item_sprite{items_texture};

private:
    std::vector<Dialog_node> dialog_graf{};
    uint32_t current_dialog_node_id{};
    uint32_t input_nodes_offset{};
    Texture_changer tex_changer{};
    sf::Font font{};
};

}

#endif // AZOYA_SUITCASE_HPP
