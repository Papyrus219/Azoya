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
    currently_parsed_npc.dialog_graf.push_back({});
    currently_parsed_npc.dialog_graf.back().node_mode = Node_mode::NONE;
    currently_parsed_npc.dialog_graf.back().next_node_mode = Node_mode::DIALOG;

    currently_parsed_npc.dialog_graf.back().next_node_id = 1;

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

        std::clog << line_count << " " << line << '\n';
        Parse_line(line);
        pos = end + 1;
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
            auto name_start_pos = line.find('{') + 1;
            auto name_end_pos = line.find('}');

            name = line.substr(name_start_pos, name_end_pos - name_start_pos);

            line_mode = Line_mode::FONT_PATH;
            break;
        }
        case Line_mode::FONT_PATH:
        {
            if(!currently_parsed_npc.font.openFromFile(line))
            {
                std::cerr << "ERROR::NPC_PARSER::Failed to open font: " << line << '\n';
            }


            currently_parsed_npc.dialog_box.Init(name, currently_parsed_npc.font, sf::Color::Cyan, sf::Color::Green);

            line_mode = Line_mode::NONE;
            break;
        }
        case Line_mode::DIALOG_DECLARATION:
        {
            Dialog_node new_node{};
            new_node.node_mode = Node_mode::DIALOG;

            auto id_start_pos = line.find('[') + 1;
            auto id_end_pos = line.find(']');

            auto id = line.substr(id_start_pos, id_end_pos - id_start_pos);
            std::clog << "ID: " << id << '\n';

            Convert_string_to_number(id, current_id, "Dialog id");

            auto dialog_start_pos = line.find_first_not_of("] ", id_end_pos);
            auto dialog_end_pos = line.find_first_of('~');
            auto dialog = line.substr(dialog_start_pos, dialog_end_pos - dialog_start_pos);

            std::clog << "Dialog: " << dialog << '\n';

            new_node.dialog_text_id = currently_parsed_npc.dialog_box.Add_dialog_option(dialog);

            auto next_id_start_pos = line.find_first_of('~') + 1;
            auto next_id_end_pos = line.find_last_of('~');
            auto next_id = line.substr(next_id_start_pos, next_id_end_pos - next_id_start_pos);

            std::clog << "Next id: " << next_id << '\n';

            if(next_id[0] == '?')
            {
                new_node.next_node_mode = Node_mode::INPUT;
                next_id_start_pos++;
            }
            else if(next_id[0] == '!')
            {
                new_node.next_node_mode = Node_mode::FUNCTION;
                next_id_start_pos++;
            }
            else
            {
                new_node.next_node_mode = Node_mode::DIALOG;
            }

            next_id = line.substr(next_id_start_pos, next_id_end_pos - next_id_start_pos);
            Convert_string_to_number(next_id, new_node.next_node_id, "Next id");

            currently_parsed_npc.dialog_graf.push_back(new_node);

            line_mode = Line_mode::NONE;
            break;
        }
    }
}
