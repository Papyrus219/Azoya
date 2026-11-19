#ifndef AZOYA_NPC_PARSER_HPP
#define AZOYA_NPC_PARSER_HPP

#include <Azoya/npc.hpp>
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
        DIALOG_DECLARATION,
    } line_mode;

public:
    Npc Parse_npc_config_file(const std::filesystem::path & path);

private:
    void Parse_line(std::string_view line);

    Npc currently_parsed_npc{};

    std::ifstream file{};
    std::size_t line_count{};
    std::string buffor{};
};

}

#endif // AZOYA_NPC_PARSER_HPP
