#include <Azoya/npc.hpp>
#include <Azoya/npc_parser.hpp>

using namespace azoya;

azoya::Npc_parser azoya::Npc::parser{};

void azoya::Npc::Click(sf::Vector2f mouse_pos)
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
            std::clog << "Mode -> Current: " << Node_mode_to_string(dialog_graf[current_dialog_node_id].node_mode) << " Next: " << Node_mode_to_string(dialog_graf[current_dialog_node_id].next_node_mode) << '\n';

            switch(dialog_graf[current_dialog_node_id].node_mode)
            {
                case Node_mode::NONE:
                    break;
                case Node_mode::DIALOG:
                    dialog_box.Set_dialog_option( dialog_graf[ current_dialog_node_id ].dialog_text_id );
                    sprite.setTextureRect( tex_changer.Get_variant_rect( dialog_graf[current_dialog_node_id].sprite_variant_id ) );
                    break;
                case Node_mode::INPUT:
                    input_box.Set_option_pack( dialog_graf[current_dialog_node_id].dialog_text_id );
                    sprite.setTextureRect( tex_changer.Get_variant_rect( dialog_graf[current_dialog_node_id].sprite_variant_id ) );
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
                sprite.setTextureRect( tex_changer.Get_variant_rect( dialog_graf[current_dialog_node_id].sprite_variant_id ) );
            }

            break;
        }
        case Node_mode::FUNCTION:
        {
            break;
        }
    }

    if(dialog_graf[current_dialog_node_id].node_mode == Node_mode::DIALOG)
    {

    }

}

std::string_view azoya::Npc::Node_mode_to_string(Node_mode mode)
{
    switch(mode)
    {
        case Node_mode::NONE:
            return "NONE";
        case Node_mode::DIALOG:
            return "DIALOG";
        case Node_mode::INPUT:
            return "INPUT";
        case Node_mode::FUNCTION:
            return "FUNCTION";
    }
}

