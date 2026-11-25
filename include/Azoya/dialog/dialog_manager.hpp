#ifndef AZOYA_DIALOG_MANAGER_HPP
#define AZOYA_DIALOG_MANAGER_HPP

#include <Azoya/event_manager.hpp>
#include <Azoya/dialog/dialog_box.hpp>
#include <Azoya/dialog/input_box.hpp>
#include <Azoya/dialog/dialog_node.hpp>
#include <Azoya/texture_changer.hpp>
#include <vector>
#include <unordered_map>

namespace azoya
{

class Dialog_parser;

class Dialog_manager
{
public:
    void Click(sf::Vector2f mouse_pos);
    void Update(sf::Vector2f mouse_pos);
    void React_to_dialog_event(std::string_view event_name);

    Node_mode Get_mode() {return graf[current_node_id].node_mode;}

    sf::Texture texture{};
    sf::Sprite sprite{texture};

    static Dialog_parser parser;
    static Event_manager * event_manager;

    Dialog_box dialog_box{};
    Input_box input_box{};

private:
    Dialog_manager() = default;

    std::string_view Node_mode_to_string(Node_mode mode);

    std::vector <Dialog_node> graf{};
    uint32_t current_node_id{};

    uint32_t input_offset{};
    uint32_t event_offset{};

    std::unordered_map<uint32_t, std::string> events_name{};
    std::unordered_map<std::string, uint> event_bookmarks{};

    Texture_changer tex_changer{};

    sf::Font font{};

    friend class Dialog_parser;
};

}

#endif // AZOYA_DIALOG_MANAGER_HPP
