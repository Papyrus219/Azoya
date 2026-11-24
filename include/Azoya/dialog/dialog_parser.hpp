#ifndef AZOYA_DIALOG_PARSER_HPP
#define AZOYA_DIALOG_PARSER_HPP

#include <Azoya/dialog/dialog_box.hpp>
#include <Azoya/dialog/input_box.hpp>
#include <Azoya/dialog/dialog_node.hpp>
#include <Azoya/texture_changer.hpp>
#include <SFML/Graphics.hpp>
#include <string_view>
#include <iostream>

namespace azoya
{

struct Dialog_parser_pack
{
    Dialog_box * dialog_box{};
    Input_box * input_box{};
    std::vector<Dialog_node> * graf{};
    sf::Font * font{};
    sf::Texture * texture{};
    sf::Sprite * sprite{};
    Texture_changer * tex_changer{};
    uint32_t * input_nodes_offset{};
};

class Dialog_parser
{
public:
    void Start_parsing(std::string_view buffor, size_t & pos, const Dialog_parser_pack & pack);

private:
    void Parse_line(std::string_view line, const Dialog_parser_pack & pack);

    sf::Color Parse_color(std::string_view line);

    template<typename T>
    void Convert_string_to_number(std::string_view str, T & var, std::string_view var_name = "NOT GIVEN");

    std::string_view name{};
    bool is_name{};

    uint32_t current_id{};

    std::vector<std::string_view> tmp_input_texts{};
    std::vector<uint32_t> tmp_input_results{};

    sf::Color dialog_bg_color{};
    sf::Color dialog_bor_color{};
    sf::Color dialog_text_color{};

    sf::Color input_bg_color{};
    sf::Color input_bor_color{};
    sf::Color input_text_color{};

    enum class Line_mode
    {
        NONE,
        NAME_DECLARATION,
        FONT_PATH,
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
        INPUT_OPTION,
    } line_mode{};
};

template<typename T>
void azoya::Dialog_parser::Convert_string_to_number(std::string_view str, T & var, std::string_view var_name)
{
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), var);
    if(ec != std::errc{})
    {
        std::println(std::cerr, "Failed to parse variable: {}", var_name);
    }
}

}

#endif // AZOYA_DIALOG_PARSER_HPP
