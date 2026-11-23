#ifndef AZOYA_NPC_PARSER_HPP
#define AZOYA_NPC_PARSER_HPP

#include <Azoya/npc.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace azoya
{

class Npc_parser
{
private:
    enum class Line_mode
    {
        NONE,
        NAME_DECLARATION,
        FONT_PATH,
        WORLD_TEXTURE_RECT,
        DIALOG_TEXTURE_PATH,
        VARIANT_SIZE,
        DIALOG_BOX_BACKGROUND_COLOR,
        DIALOG_BOX_BORDER_COLOR,
        DIALOG_BOX_TEXT_COLOR,
        INPUT_BOX_BACKGROUND_COLOR,
        INPUT_BOX_BORDER_COLOR,
        INPUT_BOX_TEXT_COLOR,
        DIALOG_DECLARATION,
        END_OF_DIALOGS,
        INPUT_DECLARATION,
    } line_mode;

public:
    Npc Parse_npc_config_file(const std::filesystem::path & path);

    template<typename T>
    void Convert_string_to_number(std::string_view str, T & var, std::string_view var_name = "NOT GIVEN");

private:
    void Parse_line(std::string_view line);

    sf::Color Parse_color(std::string_view line);

    Npc currently_parsed_npc{};
    sf::IntRect world_tex_rect{};

    std::string_view name{};
    uint32_t current_id{};

    std::ifstream file{};
    std::size_t line_count{};
    std::string buffor{};

    sf::Color dialog_box_background_color{};
    sf::Color dialog_box_border_color{};
    sf::Color dialog_box_text_color{};

    sf::Color input_box_background_color{};
    sf::Color input_box_border_color{};
    sf::Color input_box_text_color{};
};

template<typename T>
void azoya::Npc_parser::Convert_string_to_number(std::string_view str, T & var, std::string_view var_name)
{
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), var);
    if(ec != std::errc{})
    {
        std::println(std::cerr, "Failed to parse variable: {}", var_name);
    }
}

}

#endif // AZOYA_NPC_PARSER_HPP
