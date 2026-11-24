#include <Azoya/dialog/dialog_parser.hpp>

using namespace azoya;

void azoya::Dialog_parser::Start_parsing(std::string_view buffor, size_t & pos, const Dialog_parser_pack & pack)
{
    assert(pack.dialog_box && pack.input_box && pack.graf && pack.texture && pack.font && pack.sprite && pack.tex_changer && pack.input_nodes_offset);

    line_mode = Line_mode::NAME_DECLARATION;

    while(pos < buffor.size())
    {
        size_t end = buffor.find('\n', pos);
        if(end == std::string_view::npos) end = buffor.size();

        std::string_view line = buffor.substr(pos, end - pos);
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

        Parse_line(line, pack);
        pos = end + 1;
    }
}

void azoya::Dialog_parser::Parse_line(std::string_view line, const Dialog_parser_pack & pack)
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

            is_name = !(name == "");

            line_mode = Line_mode::FONT_PATH;
            break;
        }
        case Line_mode::FONT_PATH:
        {
            if(!pack.font->openFromFile(line))
            {
                std::cerr << "ERROR::DIALOG_PARSER::Failed to open font: " << line << '\n';
            }

            pack.dialog_box->Init(name, *pack.font, sf::Color::Cyan, sf::Color::Green);
            pack.input_box->Init(*pack.font, sf::Color::Cyan, sf::Color::Green);

            line_mode = Line_mode::DIALOG_TEXTURE_PATH;
            break;
        }
        case Line_mode::DIALOG_TEXTURE_PATH:
        {
            if(!pack.texture->loadFromFile(line))
            {
                std::cerr << "ERROR::NPC_PARSER::Failed to texture font: " << line << '\n';
            }
            pack.sprite->setTexture(*pack.texture, true);

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

            pack.tex_changer->Init(*pack.texture, variant_size);
            pack.sprite->setTextureRect(pack.tex_changer->Get_variant_rect( 0 ));

            line_mode = Line_mode::DIALOG_BOX_BACKGROUND_COLOR;
            break;
        }
        case Line_mode::DIALOG_BOX_BACKGROUND_COLOR:
        {
            dialog_bg_color = Parse_color(line);
            pack.dialog_box->Set_background_color( dialog_bg_color );

            line_mode = Line_mode::DIALOG_BOX_BORDER_COLOR;
            break;
        }
        case Line_mode::DIALOG_BOX_BORDER_COLOR:
        {
            dialog_bor_color = Parse_color(line);
            pack.dialog_box->Set_outline_color( dialog_bor_color );

            line_mode = Line_mode::DIALOG_BOX_TEXT_COLOR;
            break;
        }
        case Line_mode::DIALOG_BOX_TEXT_COLOR:
        {
            dialog_text_color = Parse_color(line);
            pack.dialog_box->Set_text_color( dialog_text_color );

            line_mode = Line_mode::INPUT_BOX_BACKGROUND_COLOR;
            break;
        }
        case Line_mode::INPUT_BOX_BACKGROUND_COLOR:
        {
            input_bg_color = Parse_color(line);
            pack.input_box->Set_background_color( input_bg_color );

            line_mode = Line_mode::INPUT_BOX_BORDER_COLOR;
            break;
        }
        case Line_mode::INPUT_BOX_BORDER_COLOR:
        {
            input_bor_color = Parse_color(line);
            pack.input_box->Set_outline_color( input_bor_color );

            line_mode = Line_mode::INPUT_BOX_TEXT_COLOR;
            break;
        }
        case Line_mode::INPUT_BOX_TEXT_COLOR:
        {
            input_bg_color = Parse_color(line);
            pack.input_box->Set_text_color( input_bg_color );

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

            if(dialog != "")
            {
                std::clog << "Dialog: " << dialog << '\n';

                new_node.dialog_text_id = pack.dialog_box->Add_dialog_option(dialog);
            }
            else
            {
                new_node.node_mode = Node_mode::NONE;
            }

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

            pack.graf->push_back(new_node);

            line_mode = Line_mode::NONE;
            break;
        }
        case Line_mode::END_OF_DIALOGS:
        {
            *pack.input_nodes_offset = current_id;

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

            pack.input_box->hover_type = Input_box::Hover_type::LIGHT;
            pack.graf->push_back(new_node);
            line_mode = Line_mode::INPUT_OPTION;
            break;
        }
        case Line_mode::INPUT_OPTION:
        {
            if(line[0] == '?')
            {
                pack.graf->back().dialog_text_id = pack.input_box->Add_option_pack(tmp_input_texts, tmp_input_results);
                tmp_input_texts.clear();
                tmp_input_results.clear();

                line_mode = Line_mode::NONE;
                break;
            }

            auto next_id_start_pos = line.find_first_of('~') + 1;
            auto next_id_end_pos = line.find_first_of('~', next_id_start_pos);
            auto next_id_str = line.substr(next_id_start_pos, next_id_end_pos);

            next_id_str = line.substr(next_id_start_pos, next_id_end_pos - next_id_start_pos);
            uint32_t next_id{};

            Convert_string_to_number(next_id_str, next_id, "Next id");

            auto text_start_pos = line.find_first_not_of(" ~", next_id_end_pos);
            auto text = line.substr(text_start_pos);

            tmp_input_results.push_back( next_id );
            tmp_input_texts.push_back( text );

            break;
        }
    }
}

sf::Color azoya::Dialog_parser::Parse_color(std::string_view line)
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


