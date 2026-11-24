#include <Azoya/npc_parser.hpp>

azoya::Npc azoya::Npc_parser::Parse_npc_config_file(const std::filesystem::path & path)
{
    line_mode = Line_mode::WORLD_TEXTURE_RECT;

    currently_parsed_npc.dialog_graf.clear();
    currently_parsed_npc.dialog_graf.push_back({});
    currently_parsed_npc.dialog_graf.back().node_mode = Node_mode::NONE;
    currently_parsed_npc.dialog_graf.back().next_node_mode = Node_mode::DIALOG;

    currently_parsed_npc.dialog_graf.back().next_node_id = 1;

    currently_parsed_npc.current_dialog_node_id = 0;
    line_count = 0;

    std::ifstream file{path};
    if(!file)
    {

    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    std::string buffor = ss.str();

    std::string_view buffer_view = buffor;
    size_t pos{};
    while(pos < buffer_view.size())
    {
        size_t end = buffer_view.find('\n', pos);
        if(end == std::string_view::npos) end = buffer_view.size();
        line_count++;

        std::string_view line = buffer_view.substr(pos, end - pos);
        if(line.size() == 0 || line[0] == '#') //If line empty or comment = skip.
        {
            pos = end + 1;
            continue;
        }

        std::clog << line_count << " " << line << '\n';
        Parse_line(line);
        pos = end + 1;

        if(line_mode == Line_mode::DIALOG_START)
        {
            Dialog_parser_pack pack{.dialog_box = &currently_parsed_npc.dialog_box, .input_box = &currently_parsed_npc.input_box, .graf = &currently_parsed_npc.dialog_graf, .font = &currently_parsed_npc.font, .texture = &currently_parsed_npc.dialog_texture, .sprite = &currently_parsed_npc.dialog_sprite, .tex_changer = &currently_parsed_npc.tex_changer, .input_nodes_offset = &currently_parsed_npc.input_nodes_offset};

            dialog_parser.Start_parsing(buffer_view, pos, pack);
        }
    }

    return currently_parsed_npc;
}

void azoya::Npc_parser::Parse_line(std::string_view line)
{
    switch(line_mode)
    {
        case Line_mode::WORLD_TEXTURE_RECT:
        {
            auto pos_x_start_pos = line.find_first_not_of(" ");
            auto pos_x_end_pos = line.find_first_of(" ", pos_x_start_pos);
            auto pos_x_str = line.substr(pos_x_start_pos, pos_x_end_pos - pos_x_start_pos);

            Convert_string_to_number(pos_x_str, world_tex_rect.position.x, "World tex pos x");

            auto pos_y_start_pos = line.find_first_not_of(" ", pos_x_end_pos);
            auto pos_y_end_pos = line.find_first_of(" ", pos_y_start_pos);
            auto pos_y_str = line.substr(pos_y_start_pos, pos_y_end_pos - pos_y_start_pos);

            Convert_string_to_number(pos_y_str, world_tex_rect.position.y, "World tex pos y");

            auto size_x_start_pos = line.find_first_not_of(" ", pos_y_end_pos);
            auto size_x_end_pos = line.find_first_of(" ", size_x_start_pos);
            auto size_x_str = line.substr(size_x_start_pos, size_x_end_pos - size_x_start_pos);

            Convert_string_to_number(size_x_str, world_tex_rect.size.x, "World tex size x");

            auto size_y_start_pos = line.find_first_not_of(" ", size_x_end_pos);
            auto size_y_end_pos = line.find_first_of(" ", size_y_start_pos);
            auto size_y_str = line.substr(size_y_start_pos, size_y_end_pos - size_y_start_pos);

            Convert_string_to_number(size_y_str, world_tex_rect.size.y, "World tex size y");

            currently_parsed_npc.world_sprite.setTexture(currently_parsed_npc.world_texture, true);
            currently_parsed_npc.world_sprite.setTextureRect(world_tex_rect);

            line_mode = Line_mode::DIALOG_START;
            break;
        }
        case Line_mode::DIALOG_START:
        {
            break;
        }
    }
}
