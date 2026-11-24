#include <Azoya/dialog/dialog_box.hpp>
#include <iostream>

using namespace azoya;

void azoya::Dialog_box::Init(const sf::String & name, const sf::Font & font, sf::Color background_color, sf::Color border_color, bool is_name_enabled, std::optional<std::reference_wrapper<sf::Sound>> letter_sound)
{
    this->font = font;

    box.setFillColor( background_color );
    box.setOutlineThickness(8);
    box.setOutlineColor(border_color);

    box.setSize({1000, 400});
    box.setPosition({100, 500});

    current_animation_text.setFont(font);
    current_animation_text.setCharacterSize(35);
    current_animation_text.setFillColor( sf::Color::Black );
    current_animation_text.setPosition( (box.getPosition() + sf::Vector2f{5, 5}) );

    this->name.setString(name);
    this->name.setCharacterSize(50);
    this->name.setFillColor( sf::Color::Black );
    this->name.setFont(font);

    sf::Vector2f name_size = this->name.getLocalBounds().size;
    name_box.setSize( name_size + sf::Vector2f{40, 20} );
    name_box.setPosition( box.getPosition() - sf::Vector2f{ 0, name_box.getSize().y } );
    name_box.setFillColor( background_color );
    name_box.setOutlineThickness(8);
    name_box.setOutlineColor( border_color );
    name_box.setOutlineColor(border_color);

    this->name.setPosition( name_box.getPosition() + sf::Vector2f{20, 0} );

    if(letter_sound)
    {
        this->letter_sound = letter_sound;
    }

    this->is_name_enabled = is_name_enabled;

    Set_text_speed( Text_speed::NORMAL );
}

void azoya::Dialog_box::Update()
{
    if(is_animation_running)
    {
        auto time_elapsed = animation_clock.getElapsedTime();
        auto time_elapsed_copy = time_elapsed;

        while(time_elapsed >= letter_apperence_durration)
        {
            if(letter_sound)
            {
                letter_sound->get().play();
            }
            current_animation_text.setString( current_animation_text.getString() + dialogs_content[current_dialog_id].getString()[current_animation_letter_id]);
            current_animation_letter_id++;
            if(current_animation_letter_id >= dialogs_content[current_dialog_id].getString().getSize())
            {
                current_animation_letter_id = 0;
                current_animation_text.setString("");
                is_animation_running = false;
                animation_clock.stop();
            }

            time_elapsed -= letter_apperence_durration;
        }

        if(time_elapsed_copy > letter_apperence_durration)
        {
            animation_clock.restart();
        }
    }
}

uint32_t azoya::Dialog_box::Add_dialog_option(const sf::String & content)
{
    dialogs_content.emplace_back(font, content);
    dialogs_content.back().setCharacterSize(35);
    dialogs_content.back().setFillColor( sf::Color::Black );
    dialogs_content.back().setPosition( (box.getPosition() + sf::Vector2f{5, 5}) );

    Format_text( dialogs_content.size() - 1 );

    return dialogs_content.size() - 1;
}

void azoya::Dialog_box::Set_dialog_option(uint32_t id)
{
    if(id >= dialogs_content.size())
    {
        std::cerr << "ERROR::DIALOG BOX::Setting dialog box that is not exist!\n";
        return;
    }

    current_dialog_id = id;

    is_animation_running = true;
    current_animation_letter_id = 0;
    current_animation_text.setString("");
    animation_clock.restart();
}

void azoya::Dialog_box::Set_name(const sf::String & name)
{
    this->name.setString( name );

    sf::Vector2f name_size = this->name.getLocalBounds().size;
    name_box.setSize( name_size + sf::Vector2f{40, 20} );
}

void azoya::Dialog_box::Set_text_speed(Text_speed speed)
{
    switch(speed)
    {
        case Text_speed::SLOW:
            letter_apperence_durration = sf::seconds(0.02);
            break;
        case Text_speed::NORMAL:
            letter_apperence_durration = sf::seconds(0.1);
            break;
        case Text_speed::FAST:
            letter_apperence_durration = sf::seconds(0.005);
            break;
    }
}

void azoya::Dialog_box::Set_position(sf::Vector2f new_position)
{
    box.setPosition( new_position );
    for(auto & text : dialogs_content)
    {
        text.setPosition( new_position + sf::Vector2f{5, 5});
    }
    current_animation_text.setPosition( new_position + sf::Vector2f{5, 5} );
    name_box.setPosition( box.getPosition() - sf::Vector2f{ 0, name_box.getSize().y + name_box.getOutlineThickness() } );
    this->name.setPosition( name_box.getPosition() + sf::Vector2f{20, -10} );
}

void azoya::Dialog_box::Set_size(sf::Vector2f new_size)
{
    box.setSize( new_size );
    name_box.setPosition( box.getPosition() - sf::Vector2f{ 0, name_box.getSize().y } );

    for(auto i{0UZ}; i < dialogs_content.size(); i++)
    {
        Unformat_text(i);
        Format_text(i);
    }

    is_animation_running = true;
    current_animation_letter_id = 0;
    current_animation_text.setString("");
    animation_clock.restart();
}

void azoya::Dialog_box::Set_background_color(sf::Color new_color)
{
    box.setFillColor( new_color );
    name_box.setFillColor( new_color );
}

void azoya::Dialog_box::Set_outline_color(sf::Color new_color)
{
    box.setOutlineColor( new_color );
    name_box.setOutlineColor( new_color );
}

void azoya::Dialog_box::Set_text_color(sf::Color new_color)
{
    for(auto & text : dialogs_content)
    {
        text.setFillColor( new_color );
    }

    current_animation_text.setFillColor( new_color );
     name.setFillColor( new_color );
}

void azoya::Dialog_box::Set_character_size(uint16_t new_size)
{
    for(auto & text : dialogs_content)
    {
        text.setCharacterSize( new_size );;
    }

    current_animation_text.setCharacterSize( new_size );
}

void azoya::Dialog_box::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(box, states);

    if(is_name_enabled)
    {
        target.draw(name_box, states);
        target.draw(name, states);
    }

    if(is_animation_running)
    {
        target.draw(current_animation_text);
    }
    else
    {
        target.draw(dialogs_content[current_dialog_id], states);
    }
}

void azoya::Dialog_box::Unformat_text(uint32_t which)
{
    auto & text = dialogs_content[which];

    sf::String str = text.getString();
    str.replace("\n", " ");
    text.setString(str);
}

void azoya::Dialog_box::Format_text(uint32_t which)
{
    auto box_length = box.getGlobalBounds().size.x - box.getGlobalBounds().position.x;

    std::clog << "FORMAT: box size: " << box_length << '\n';

    sf::Text line{font};
    sf::Text copy = dialogs_content[ which ];
    sf::Text word{font};

    line.setString("");
    dialogs_content[ which ].setString("");
    word.setString("");

    line.setCharacterSize( dialogs_content[ which ].getCharacterSize() );
    word.setCharacterSize( word.getCharacterSize() );

    for(auto c : copy.getString())
    {
        if(c == ' ')
        {
            auto line_length = line.getGlobalBounds().size.x - line.getGlobalBounds().position.x;
            auto word_length = word.getGlobalBounds().size.x - word.getGlobalBounds().position.x;

            if( (line_length + word_length + 90) >= box_length - 16)
            {
                dialogs_content[which].setString( dialogs_content[which].getString() + line.getString() + '\n' );
                line.setString("");
            }
            else
            {
                line.setString( line.getString() + ' ' );
            }

            line.setString( line.getString() + word.getString() );
            word.setString("");
        }
        else
        {
            word.setString( word.getString() + c);
        }
    }

    dialogs_content[which].setString(dialogs_content[which].getString() + line.getString() + " " + word.getString() + '\n' );
}

