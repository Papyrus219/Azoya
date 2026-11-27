#include <Azoya/dialog/dialog_manager.hpp>
#include <Azoya/dialog/dialog_parser.hpp>
#include <iostream>

azoya::Dialog_parser azoya::Dialog_manager::parser{};
azoya::Event_manager * azoya::Dialog_manager::event_manager{};

void azoya::Dialog_manager::Update(sf::Vector2f mouse_pos)
{
    switch(graf[current_node_id].node_mode)
    {
        case Node_mode::NONE:
            break;
        case Node_mode::DIALOG:
            dialog_box.Update();
            break;
        case Node_mode::INPUT:
            input_box.Update(mouse_pos);
            break;
        case Node_mode::FUNCTION:
            break;
    }
}

void azoya::Dialog_manager::Click(sf::Vector2f mouse_pos)
{
    switch(graf[current_node_id].node_mode)
    {
        case Node_mode::NONE:
            [[fallthrough]];
        case Node_mode::DIALOG:
        {
            uint32_t offset{};

            switch(graf[current_node_id].next_node_mode)
            {
                case Node_mode::NONE:
                    break;
                case Node_mode::DIALOG:
                    break;
                case Node_mode::INPUT:
                    offset = input_offset;
                    break;
                case Node_mode::FUNCTION:
                    break;
            }

            current_node_id = graf[ current_node_id ].next_node_id + offset;

            std::wclog << "Dialog: " << current_node_id << " -> " << graf[current_node_id].dialog_text_id << '\n';
            std::wclog << "Mode -> Current: " << Node_mode_to_string(graf[current_node_id].node_mode) << " Next: " << Node_mode_to_string(graf[current_node_id].next_node_mode) << '\n';

            switch(graf[current_node_id].node_mode)
            {
                case Node_mode::NONE:
                    break;
                case Node_mode::DIALOG:
                    dialog_box.Set_dialog_option( graf[ current_node_id ].dialog_text_id );
                    sprite.setTextureRect( tex_changer.Get_variant_rect( graf[current_node_id].sprite_variant_id ) );
                    break;
                case Node_mode::INPUT:
                    input_box.Set_option_pack( graf[current_node_id].dialog_text_id );
                    sprite.setTextureRect( tex_changer.Get_variant_rect( graf[current_node_id].sprite_variant_id ) );
                    break;
                case Node_mode::FUNCTION:
                    break;
            }

            std::wclog << "IN MOMENT OF CHECK HAVE: " << current_node_id << '\n';
            if(graf[current_node_id].event_id)
            {
                std::wclog << "EVENT!\n";
                event_manager->Annouce_event( events_name[*graf[current_node_id].event_id] );
            }

            break;
        }
        case Node_mode::INPUT:
        {
            auto result = input_box.Click( mouse_pos );
            if(result)
            {
                current_node_id = result.value();

                dialog_box.Set_dialog_option( graf[current_node_id].dialog_text_id );
                sprite.setTextureRect( tex_changer.Get_variant_rect( graf[current_node_id].sprite_variant_id ) );

                std::wclog << "IN MOMENT OF CHECK HAVE: " << current_node_id << '\n';
                if(graf[current_node_id].event_id)
                {
                    std::wclog << "EVENT!\n";
                    event_manager->Annouce_event( events_name[*graf[current_node_id].event_id] );
                }
            }

            break;
        }
        case Node_mode::FUNCTION:
        {
            break;
        }
    }
    std::wclog << "NOW HAVE: " << current_node_id << "\n";
    if( graf[current_node_id].event_id )
    {
        std::wclog << "HAVE EVENT!\n";
    }
}

void azoya::Dialog_manager::React_to_dialog_event(std::wstring_view event_name)
{
    auto bookmark_it = event_bookmarks.find( std::wstring{event_name});

    if(bookmark_it != event_bookmarks.end())
    {
        std::wclog << "MATCH!\n";

        current_node_id = bookmark_it->second;

        dialog_box.Set_dialog_option( graf[current_node_id].dialog_text_id );
        sprite.setTextureRect( tex_changer.Get_variant_rect( graf[current_node_id].sprite_variant_id ) );
    }
}

std::wstring_view azoya::Dialog_manager::Node_mode_to_string(Node_mode mode)
{
    switch(mode)
    {
        case Node_mode::NONE:
            return L"NONE";
        case Node_mode::DIALOG:
            return L"DIALOG";
        case Node_mode::INPUT:
            return L"INPUT";
        case Node_mode::FUNCTION:
            return L"FUNCTION";
    }

    return L"";
}
