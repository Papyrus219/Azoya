#ifndef AZOYA_NPC_PARSER_HPP
#define AZOYA_NPC_PARSER_HPP

#include <Azoya/npc.hpp>
#include <Azoya/dialog/dialog_parser.hpp>
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
        WORLD_TEXTURE_RECT,
        DIALOG_START,
    } line_mode;

public:
    Npc Parse_npc_config_file(const std::filesystem::path & path);

    template<typename T>
    void Convert_string_to_number(std::wstring_view str, T & var, std::string_view var_name = "NOT GIVEN");

private:
    void Parse_line(std::wstring_view line);

    Dialog_parser dialog_parser{};

    Npc currently_parsed_npc{};
    sf::IntRect world_tex_rect{};

    std::wstring_view name{};
    uint32_t current_id{};

    std::ifstream file{};
    std::size_t line_count{};
    std::wstring buffor{};

    sf::Color dialog_box_background_color{};
    sf::Color dialog_box_border_color{};
    sf::Color dialog_box_text_color{};

    sf::Color input_box_background_color{};
    sf::Color input_box_border_color{};
    sf::Color input_box_text_color{};
};

template<typename T>
void azoya::Npc_parser::Convert_string_to_number(std::wstring_view str, T & var, std::string_view var_name)
{
    try
    {
        var = static_cast<T>(std::stof( std::wstring{str}));
    }
    catch(const std::exception & except)
    {
        std::cerr << "Failed to parse variable: " << var_name << '\n';
    }
}

}

#endif // AZOYA_NPC_PARSER_HPP
