#include <Azoya/npc_parser.hpp>

azoya::Npc azoya::Npc_parser::Parse_npc_config_file(const std::filesystem::path & path)
{
    std::ifstream file{path};
    if(!file)
    {

    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    buffor = ss.str();
    line_mode = Line_mode::NONE;

    currently_parsed_npc.dialog_graf.clear();
    currently_parsed_npc.current_dialog_node_id = 0;
    line_count = 0;

    std::string_view buffer_view = buffor;
    size_t pos{};
    while(pos < buffer_view.size())
    {
        size_t end = buffer_view.find('\n', pos);
        if(end == std::string_view::npos) end = buffer_view.size();
        line_count++;

        std::string_view line = buffer_view.substr(pos, end - pos);
        if(line.size() == 0) //If line empty = skip.
        {
            pos = end + 1;
            continue;
        }

        if(line_mode == Line_mode::NONE) //If none mode select it
        {
            switch(line[0])
            {
                case '{':
                    line_mode = Line_mode::NAME_DECLARATION;
                    break;
                case '[':
                    line_mode = Line_mode::DIALOG_DECLARATION;
                    break;
            }
        }

        Parse_line(line);
    }

    return currently_parsed_npc;
}

void azoya::Npc_parser::Parse_line(std::string_view line)
{
    switch(line_mode)
    {
        case Line_mode::NONE:
        {
            break;
        }
        case Line_mode::NAME_DECLARATION:
        {
            break;
        }
        case Line_mode::DIALOG_DECLARATION:
        {
            break;
        }
    }
}
