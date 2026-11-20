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
        DIALOG_DECLARATION,
        END_OF_DIALOGS,
    } line_mode;

public:
    Npc Parse_npc_config_file(const std::filesystem::path & path);

    template<typename T>
    void Convert_string_to_number(std::string_view str, T & var, std::string_view var_name = "NOT GIVEN");

private:
    void Parse_line(std::string_view line);

    Npc currently_parsed_npc{};

    std::string_view name{};
    uint32_t current_id{};

    std::ifstream file{};
    std::size_t line_count{};
    std::string buffor{};
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
