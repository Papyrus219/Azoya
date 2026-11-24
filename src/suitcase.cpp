#include "Azoya/suitcase.hpp"
#include <fstream>

void azoya::Suitcase::Init(const std::filesystem::path & path)
{
    std::ifstream file{path};
    if(!file)
    {

    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    std::string buffor = ss.str();

    dialog_graf.clear();
    dialog_graf.push_back({});
    dialog_graf.back().node_mode = Node_mode::NONE;
    dialog_graf.back().next_node_mode = Node_mode::DIALOG;

    dialog_graf.back().next_node_id = 1;

    Dialog_parser_pack pack{.dialog_box = &dialog_box, .input_box = &input_box, .graf = &dialog_graf, .font = &font, .texture = &items_texture, .sprite = &item_sprite, .tex_changer = &tex_changer, .input_nodes_offset = &input_nodes_offset};

    size_t pos{0};
    dialog_parser.Start_parsing(buffor, pos, pack);
}

void azoya::Suitcase::Click(sf::Vector2f mouse_pos)
{
    switch(dialog_graf[current_dialog_node_id].node_mode)
    {
        case Node_mode::NONE:
            [[fallthrough]];
        case Node_mode::DIALOG:
        {
            uint32_t offset{};

            switch(dialog_graf[current_dialog_node_id].next_node_mode)
            {
                case Node_mode::NONE:
                    break;
                case Node_mode::DIALOG:
                    break;
                case Node_mode::INPUT:
                    offset = input_nodes_offset;
                    break;
                case Node_mode::FUNCTION:
                    break;
            }

            current_dialog_node_id = dialog_graf[ current_dialog_node_id ].next_node_id + offset;

            std::clog << "Dialog: " << current_dialog_node_id << " -> " << dialog_graf[current_dialog_node_id].dialog_text_id << '\n';

            switch(dialog_graf[current_dialog_node_id].node_mode)
            {
                case Node_mode::NONE:
                    break;
                case Node_mode::DIALOG:
                    dialog_box.Set_dialog_option( dialog_graf[ current_dialog_node_id ].dialog_text_id );
                    item_sprite.setTextureRect( tex_changer.Get_variant_rect( dialog_graf[current_dialog_node_id].sprite_variant_id ) );
                    break;
                case Node_mode::INPUT:
                    input_box.Set_option_pack( dialog_graf[current_dialog_node_id].dialog_text_id );
                    item_sprite.setTextureRect( tex_changer.Get_variant_rect( dialog_graf[current_dialog_node_id].sprite_variant_id ) );
                    break;
                case Node_mode::FUNCTION:
                    break;
            }

            break;
        }
                case Node_mode::INPUT:
                {
                    auto result = input_box.Click( mouse_pos );
                    if(result)
                    {
                        current_dialog_node_id = result.value();

                        dialog_box.Set_dialog_option( dialog_graf[current_dialog_node_id].dialog_text_id );
                        item_sprite.setTextureRect( tex_changer.Get_variant_rect( dialog_graf[current_dialog_node_id].sprite_variant_id ) );
                    }

                    break;
                }
                case Node_mode::FUNCTION:
                {
                    break;
                }
    }
}
