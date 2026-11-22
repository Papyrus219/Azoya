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

    option_1_box.setSize( box_size );
    option_1_box.setPosition( main_box.getPosition() );
    option_1_box.setFillColor( background_color);
    option_1_box.setOutlineColor( border_color );
    option_1_box.setOutlineThickness( 8 );

    option_2_box.setSize( box_size );
    option_2_box.setPosition( main_box.getPosition() + sf::Vector2f{0, box_size.y} );
    option_2_box.setFillColor( background_color );
    option_2_box.setOutlineColor( border_color );
    option_2_box.setOutlineThickness( 8 );

    this->font = font;

    this->background_color = background_color;
    this->hover_type = hover_type;

    Add_option_pack("PLACEHOLEDER1", "PLACEHOLEDER2", 3, 4);
}

void azoya::Input_box::Update(sf::Vector2f mouse_pos)
{
    if(option_1_box.getGlobalBounds().contains(mouse_pos))
    {
        if(hover_type == Hover_type::LIGHT)
        {
            option_1_box.setFillColor( background_color + sf::Color{50, 50, 50} );
        }
        else
        {
            option_1_box.setFillColor( background_color - sf::Color{50, 50, 50} );
        }

        option_2_box.setFillColor( background_color );
    }
    else if(option_2_box.getGlobalBounds().contains(mouse_pos))
    {
        option_1_box.setFillColor( background_color );

        if(hover_type == Hover_type::LIGHT)
        {
            option_2_box.setFillColor( background_color + sf::Color{50, 50, 50} );
        }
        else
        {
            option_2_box.setFillColor( background_color - sf::Color{50, 50, 50} );
        }
    }
    else
    {
        option_1_box.setFillColor( background_color );
        option_2_box.setFillColor( background_color );
    }
}

uint32_t azoya::Input_box::Add_option_pack(const sf::String & text_1, const sf::String & text_2, uint32_t result_1, uint32_t result_2)
{
    options_packs.emplace_back(font);
    options_packs.back().text_1.setString( text_1 );
    options_packs.back().text_2.setString( text_2 );

    options_packs.back().text_1.setCharacterSize( 35 );
    options_packs.back().text_2.setCharacterSize( 35 );

    options_packs.back().text_1.setPosition( option_1_box.getPosition() + sf::Vector2f{5, 5} );
    options_packs.back().text_2.setPosition( option_2_box.getPosition() + sf::Vector2f{5, 5} );

    options_packs.back().text_1.setFillColor( text_color );
    options_packs.back().text_2.setFillColor( text_color );

    options_packs.back().result_1 = result_1;
    options_packs.back().result_2 = result_2;

    return options_packs.size() - 1;
}

void azoya::Input_box::Set_option_pack(uint32_t pack_id)
{
    current_option_id = pack_id;
}

std::optional<uint32_t> azoya::Input_box::Click(sf::Vector2f mouse_pos)
{
    if(option_1_box.getGlobalBounds().contains(mouse_pos))
    {
        return options_packs[current_option_id].result_1;
    }
    if(option_2_box.getGlobalBounds().contains(mouse_pos))
    {
        return options_packs[current_option_id].result_2;
    }

    return {};
}

void azoya::Input_box::Set_background_color(sf::Color new_color)
{
    background_color = new_color;

    main_box.setFillColor( new_color );
    option_1_box.setFillColor( new_color );
    option_2_box.setFillColor( new_color );
}

void azoya::Input_box::Set_outline_color(sf::Color new_color)
{
    main_box.setOutlineColor( new_color );
    option_1_box.setOutlineColor( new_color );
    option_2_box.setOutlineColor( new_color );
}

void azoya::Input_box::Set_text_color(sf::Color new_color)
{
    text_color = new_color;

    for(auto & pack : options_packs)
    {
        pack.text_1.setFillColor( new_color );
        pack.text_2.setFillColor( new_color );
    }
}

azoya::Input_box::Option_pack::Option_pack(const sf::Font & font): text_1{font}, text_2{font}
{

}

void azoya::Input_box::draw(sf::RenderTarget & target, sf::RenderStates strates) const
{
    target.draw(main_box, strates);
    target.draw(option_1_box, strates);
    target.draw(option_2_box, strates);
    target.draw(options_packs[current_option_id].text_1, strates);
    target.draw(options_packs[current_option_id].text_2, strates);
}


