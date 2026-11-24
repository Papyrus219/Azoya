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
        if(line.size() == 0 || line[0] == '#') //If line empty or comment = skip.
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
                case '@':
                    line_mode = Line_mode::END_OF_DIALOGS;
                    break;
                case '?':
                    line_mode = Line_mode::INPUT_DECLARATION;
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
            currently_parsed_npc.input_box.Init(currently_parsed_npc.font, sf::Color::Cyan, sf::Color::Green);

            line_mode = Line_mode::WORLD_TEXTURE_RECT;
            break;
        }
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

            line_mode = Line_mode::DIALOG_TEXTURE_PATH;
            break;
        }
        case Line_mode::DIALOG_TEXTURE_PATH:
        {
            if(!currently_parsed_npc.dialog_texture.loadFromFile(line))
            {
                std::cerr << "ERROR::NPC_PARSER::Failed to texture font: " << line << '\n';
            }
            currently_parsed_npc.dialog_sprite.setTexture(currently_parsed_npc.dialog_texture, true);

            line_mode = Line_mode::VARIANT_SIZE;
            break;
        }
        case Line_mode::VARIANT_SIZE:
        {
            sf::Vector2i variant_size{};

            auto x_start_pos = line.find_first_not_of(" ");
            auto x_end_pos = line.find_first_of(" ", x_start_pos);
            auto x_str = line.substr(x_start_pos, x_end_pos - x_start_pos);

            Convert_string_to_number(x_str, variant_size.x, "Variant x");

            auto y_start_pos = line.find_first_not_of(" ", x_end_pos);
            auto y_end_pos = line.find_first_of(" ", y_start_pos);;
            auto y_str = line.substr(y_start_pos, y_end_pos - y_start_pos);

            Convert_string_to_number(y_str, variant_size.y, "Variant y");

            currently_parsed_npc.tex_changer.Init(currently_parsed_npc.dialog_texture, variant_size);
            currently_parsed_npc.dialog_sprite.setTextureRect( currently_parsed_npc.tex_changer.Get_variant_rect( 0 ) );

            line_mode = Line_mode::DIALOG_BOX_BACKGROUND_COLOR;
            break;
        }
        case Line_mode::DIALOG_BOX_BACKGROUND_COLOR:
        {
            dialog_box_background_color = Parse_color(line);
            currently_parsed_npc.dialog_box.Set_background_color( dialog_box_background_color );

            line_mode = Line_mode::DIALOG_BOX_BORDER_COLOR;
            break;
        }
        case Line_mode::DIALOG_BOX_BORDER_COLOR:
        {
            dialog_box_border_color = Parse_color(line);
            currently_parsed_npc.dialog_box.Set_outline_color( dialog_box_border_color );

            line_mode = Line_mode::DIALOG_BOX_TEXT_COLOR;
            break;
        }
        case Line_mode::DIALOG_BOX_TEXT_COLOR:
        {
            dialog_box_text_color = Parse_color(line);
            currently_parsed_npc.dialog_box.Set_text_color( dialog_box_text_color );

            line_mode = Line_mode::INPUT_BOX_BACKGROUND_COLOR;
            break;
        }
        case Line_mode::INPUT_BOX_BACKGROUND_COLOR:
        {
            input_box_background_color = Parse_color(line);
            currently_parsed_npc.input_box.Set_background_color( input_box_background_color );

            line_mode = Line_mode::INPUT_BOX_BORDER_COLOR;
            break;
        }
        case Line_mode::INPUT_BOX_BORDER_COLOR:
        {
            input_box_border_color = Parse_color(line);
            currently_parsed_npc.input_box.Set_outline_color( input_box_border_color );

            line_mode = Line_mode::INPUT_BOX_TEXT_COLOR;
            break;
        }
        case Line_mode::INPUT_BOX_TEXT_COLOR:
        {
            input_box_text_color = Parse_color(line);
            currently_parsed_npc.input_box.Set_text_color( input_box_text_color );

            line_mode = Line_mode::NONE;
            break;
        }
        case Line_mode::DIALOG_DECLARATION:
        {
            Dialog_node new_node{};
            new_node.node_mode = Node_mode::DIALOG;

            auto id_start_pos = line.find('[') + 1;
            auto id_end_pos = line.find_first_of(':');

            auto id = line.substr(id_start_pos, id_end_pos - id_start_pos);
            std::clog << "ID: " << id << '\n';

            Convert_string_to_number(id, current_id, "Dialog id");

            auto face_id_start_pos = line.find_first_not_of(": ", id_end_pos);
            auto face_id_end_pos = line.find_first_of("]", face_id_start_pos);

            auto face_id = line.substr(face_id_start_pos, face_id_end_pos - face_id_start_pos);
            Convert_string_to_number(face_id, new_node.sprite_variant_id, "Sprite variant");

            auto dialog_start_pos = line.find_first_not_of("] ", face_id_end_pos);
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
        case Line_mode::END_OF_DIALOGS:
        {
            currently_parsed_npc.input_nodes_offset = current_id;

            line_mode = Line_mode::NONE;
            break;
        }
        case Line_mode::INPUT_DECLARATION:
        {
            Dialog_node new_node{};
            new_node.node_mode = Node_mode::INPUT;
            new_node.next_node_mode = Node_mode::DIALOG;

            auto id_start_pos = line.find_first_of('?') + 1;
            auto id_end_pos = line.find_first_of(':', id_start_pos);

            auto id = line.substr(id_start_pos, id_end_pos - id_start_pos);
            std::clog << "Input ID: " << id << '\n';

            Convert_string_to_number(id, current_id, "Dialog id");

            auto face_id_start_pos = line.find_first_not_of(": ", id_end_pos);
            auto face_id_end_pos = line.find_first_of("?", face_id_start_pos);

            auto face_id = line.substr(face_id_start_pos, face_id_end_pos - face_id_start_pos);
            Convert_string_to_number(face_id, new_node.sprite_variant_id, "Sprite variant");

            auto option_1_start_pos = line.find_first_not_of("? ", face_id_end_pos);
            auto option_1_end_pos = line.find_first_of('~', option_1_start_pos);
            auto option_1 = line.substr(option_1_start_pos, option_1_end_pos - option_1_start_pos);

            std::clog << "Option 1: " << option_1 << " | ";

            auto option_2_start_pos = line.find_first_not_of(" ~", option_1_end_pos);
            auto option_2_end_pos = line.find_first_of("~", option_2_start_pos);
            auto option_2 = line.substr(option_2_start_pos, option_2_end_pos - option_2_start_pos);

            std::clog << "Option 2: " << option_2 << '\n';

            auto result_1_start_pos = line.find_first_not_of("~ ", option_2_end_pos);
            auto result_1_end_pos = line.find_first_of("^", result_1_start_pos);
            auto result_1_str = line.substr(result_1_start_pos, result_1_end_pos - result_1_start_pos);
            uint32_t result_1{};
            Convert_string_to_number(result_1_str, result_1, "Result 1");


            auto result_2_start_pos = line.find_first_not_of("^ ", result_1_end_pos);
            auto result_2_end_pos = line.find_first_of(" ", result_2_start_pos);
            auto result_2_str = line.substr(result_2_start_pos, result_2_end_pos - result_2_start_pos);
            uint32_t result_2{};
            Convert_string_to_number(result_2_str, result_2, "Result 2");

            std::clog << "Result 2: " << result_2_str << "\n";

            new_node.dialog_text_id = currently_parsed_npc.input_box.Add_option_pack({option_1, option_2}, {result_1, result_2});
            currently_parsed_npc.input_box.hover_type = Input_box::Hover_type::LIGHT;

            currently_parsed_npc.dialog_graf.push_back(new_node);
            line_mode = Line_mode::NONE;
            break;
        }
    }
}

sf::Color azoya::Npc_parser::Parse_color(std::string_view line)
{
    sf::Color result{};

    auto red_start_pos = line.find_first_not_of(" ");
    auto red_end_pos = line.find_first_of(" ", red_start_pos);
    auto red_str = line.substr(red_start_pos, red_end_pos - red_start_pos);

    Convert_string_to_number(red_str, result.r, "Red");

    auto green_start_pos = line.find_first_not_of(" ", red_end_pos);
    auto green_end_pos = line.find_first_of(" ", green_start_pos);;
    auto green_str = line.substr(green_start_pos, green_end_pos - green_start_pos);

    Convert_string_to_number(green_str, result.g, "Green");

    auto blue_start_pos = line.find_first_not_of(" ", green_end_pos);
    auto blue_end_pos = line.find_first_of(" ", blue_start_pos);;
    auto blue_str = line.substr(blue_start_pos, blue_end_pos - blue_start_pos);

    Convert_string_to_number(blue_str, result.b, "Blue");

    std::clog << "COLOR: " << static_cast<uint32_t>(result.r) << " " << static_cast<uint32_t>(result.g) << " " << static_cast<uint32_t>(result.b) << '\n';

    return result;
}
