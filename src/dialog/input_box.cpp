#include <Azoya/dialog/input_box.hpp>
#include <iostream>

using namespace azoya;

void azoya::Input_box::Init(const sf::Font & font, sf::Color background_color, sf::Color border_color, Hover_type hover_type)
{
    main_box.setFillColor( background_color );
    main_box.setOutlineColor( border_color );

    main_box.setOutlineThickness( 8 );
    main_box.setSize( {1680, 240} );
    main_box.setPosition( {120, 832} );

    sf::Vector2f box_size = {main_box.getSize().x, main_box.getSize().y / 2};

    this->font = font;

    this->background_color = background_color;
    this->border_color = border_color;
    this->hover_type = hover_type;

    Add_option_pack({"PLACEHOLEDER1", "PLACEHOLEDER2"}, {3, 4});
}

void azoya::Input_box::Update(sf::Vector2f mouse_pos)
{
    for(uint32_t i{}; i < options_packs[current_option_id].boxes.size(); i++)
    {
        auto & box = options_packs[current_option_id].boxes[i];

        if(box.getGlobalBounds().contains(mouse_pos))
        {
            if(hover_type == Hover_type::LIGHT)
            {
                box.setFillColor( background_color + sf::Color{50, 50, 50} );
            }
            else
            {
                box.setFillColor( background_color - sf::Color{50, 50, 50} );
            }
        }
        else
        {
             box.setFillColor(background_color);
        }
    }
}


uint32_t azoya::Input_box::Add_option_pack(std::initializer_list<std::string_view> texts, std::initializer_list<uint32_t> results)
{
    assert(texts.size() == results.size());

    sf::Vector2f box_size = {main_box.getSize().x, main_box.getSize().y / texts.size()};

    options_packs.emplace_back();
    auto & option_pack = options_packs.back();

    sf::Vector2f next_box_offset{ main_box.getPosition() };
    for(uint32_t i{}; i < texts.size(); i++)
    {
        option_pack.boxes.emplace_back();
        auto & box = option_pack.boxes.back();

        box.setSize(box_size);
        box.setPosition(next_box_offset);
        box.setFillColor(background_color);
        box.setOutlineColor(border_color);
        box.setOutlineThickness(8);

        next_box_offset.y += box_size.y;

        option_pack.texts.emplace_back(font);
        auto & text = option_pack.texts.back();
        text.setString( texts.begin()[i] );
        text.setCharacterSize(35);
        text.setPosition(( box.getPosition() + sf::Vector2f{5, 5} ));
        text.setFillColor(text_color);

        option_pack.results.push_back( results.begin()[i] );
    }

    return options_packs.size() - 1;
}

void azoya::Input_box::Set_option_pack(uint32_t pack_id)
{
    current_option_id = pack_id;
}

std::optional<uint32_t> azoya::Input_box::Click(sf::Vector2f mouse_pos)
{
    for(uint32_t i{}; i < options_packs[current_option_id].boxes.size(); i++)
    {
        auto & box = options_packs[current_option_id].boxes[i];
        if(box.getGlobalBounds().contains(mouse_pos))
        {
            return options_packs[current_option_id].results[i];
        }
    }

    return {};
}

void azoya::Input_box::Set_background_color(sf::Color new_color)
{
    background_color = new_color;

    main_box.setFillColor( new_color );

    for(auto & option_pack : options_packs)
    {
        for(auto & box : option_pack.boxes)
        {
            box.setFillColor(new_color);
        }
    }
}

void azoya::Input_box::Set_outline_color(sf::Color new_color)
{
    border_color = new_color;

    main_box.setOutlineColor( new_color );

    for(auto & option_pack : options_packs)
    {
        for(auto & box : option_pack.boxes)
        {
            box.setOutlineColor(new_color);
        }
    }
}

void azoya::Input_box::Set_text_color(sf::Color new_color)
{
    text_color = new_color;

    for(auto & pack : options_packs)
    {
        for(auto & text : pack.texts)
        {
            text.setFillColor( new_color );
        }
    }
}

void azoya::Input_box::draw(sf::RenderTarget & target, sf::RenderStates strates) const
{
    target.draw(main_box, strates);

    for(auto & box : options_packs[current_option_id].boxes)
    {
        target.draw(box);
    }

    for(auto & text : options_packs[current_option_id].texts)
    {
        target.draw(text);
    }
}


