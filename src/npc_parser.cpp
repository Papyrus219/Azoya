#include <Azoya/npc_parser.hpp>

azoya::Npc azoya::Npc_parser::Parse_npc_config_file(const std::filesystem::path & path)
{
    line_mode = Line_mode::WORLD_TEXTURE_RECT;

    line_count = 0;

    std::wifstream file;
    file.imbue(std::locale("C.UTF-8"));
    file.open(path);
    if(!file)
    {
        std::cerr << "FAIL TO OPEN FILE!\n";
    }

    std::wostringstream ss{};
    ss << file.rdbuf();

    std::wstring buffor = ss.str();

    std::wstring_view buffer_view = buffor;
    size_t pos{};
    while(pos < buffer_view.size())
    {
        size_t end = buffer_view.find('\n', pos);
        if(end == std::wstring_view::npos) end = buffer_view.size();
        line_count++;

        std::wstring_view line = buffer_view.substr(pos, end - pos);
        if(line.size() == 0 || line[0] == '#') //If line empty or comment = skip.
        {
            pos = end + 1;
            continue;
        }

        std::wclog << line_count << " " << line << '\n';
        Parse_line(line);
        pos = end + 1;

        if(line_mode == Line_mode::DIALOG_START)
        {
            currently_parsed_npc.dialog_manager = dialog_parser.Parse(buffer_view, pos);
        }
    }

    return currently_parsed_npc;
}

void azoya::Npc_parser::Parse_line(std::wstring_view line)
{
    switch(line_mode)
    {
        case Line_mode::WORLD_TEXTURE_RECT:
        {
            auto pos_x_start_pos = line.find_first_not_of(L" ");
            auto pos_x_end_pos = line.find_first_of(L" ", pos_x_start_pos);
            auto pos_x_str = line.substr(pos_x_start_pos, pos_x_end_pos - pos_x_start_pos);

            Convert_string_to_number(pos_x_str, world_tex_rect.position.x, "World tex pos x");

            auto pos_y_start_pos = line.find_first_not_of(L" ", pos_x_end_pos);
            auto pos_y_end_pos = line.find_first_of(L" ", pos_y_start_pos);
            auto pos_y_str = line.substr(pos_y_start_pos, pos_y_end_pos - pos_y_start_pos);

            Convert_string_to_number(pos_y_str, world_tex_rect.position.y, "World tex pos y");

            auto size_x_start_pos = line.find_first_not_of(L" ", pos_y_end_pos);
            auto size_x_end_pos = line.find_first_of(L" ", size_x_start_pos);
            auto size_x_str = line.substr(size_x_start_pos, size_x_end_pos - size_x_start_pos);

            Convert_string_to_number(size_x_str, world_tex_rect.size.x, "World tex size x");

            auto size_y_start_pos = line.find_first_not_of(L" ", size_x_end_pos);
            auto size_y_end_pos = line.find_first_of(L" ", size_y_start_pos);
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
