#ifndef AZOYA_DIALOG_PARSER_HPP
#define AZOYA_DIALOG_PARSER_HPP

#include <Azoya/dialog/dialog_manager.hpp>
#include <Azoya/dialog/dialog_box.hpp>
#include <Azoya/dialog/input_box.hpp>
#include <Azoya/dialog/dialog_node.hpp>
#include <Azoya/texture_changer.hpp>
#include <SFML/Graphics.hpp>
#include <string_view>
#include <iostream>

namespace azoya
{

class Dialog_parser
{
public:
    Dialog_manager Parse(std::wstring_view buffor, size_t & pos);

private:
    void Parse_line(std::wstring_view line);

    sf::Color Parse_color(std::wstring_view line);

    template<typename T>
    void Convert_string_to_number(std::wstring_view str, T & var, std::string_view var_name = "NOT GIVEN");

    Dialog_manager current_manager{};

    std::wstring_view name{};
    bool is_name{};

    uint32_t current_id{};

    std::vector<std::wstring_view> tmp_input_texts{};
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
        EVENT_BOOKMARK,
        END_OF_DIALOGS,
        INPUT_DECLARATION,
        INPUT_OPTION,
        EVENT_DECLARATION,
    } line_mode{};
};

template<typename T>
void azoya::Dialog_parser::Convert_string_to_number(std::wstring_view str, T & var, std::string_view var_name)
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

#endif // AZOYA_DIALOG_PARSER_HPP
