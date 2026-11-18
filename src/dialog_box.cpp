#include <Azoya/dialog_box.hpp>
#include <iostream>

using namespace azoya;

void azoya::Dialog_box::Init(const sf::Font & font, sf::Color background_color, sf::Color border_color)
{
    this->font = font;

    box.setFillColor( background_color );
    box.setOutlineThickness(8);
    box.setOutlineColor(border_color);

    box.setSize({1000, 400});
    box.setPosition({100, 500});

    current_animation_text.setFont(font);
    current_animation_text.setCharacterSize(50);
    current_animation_text.setFillColor( sf::Color::Black );
    current_animation_text.setPosition( (box.getPosition() + sf::Vector2f{10, 20}) );

    dialogs_content.emplace_back(font, "PLACEHOLDER!");
}

void azoya::Dialog_box::Update()
{
    if(is_animation_running)
    {
        auto time_elapsed = animation_clock.getElapsedTime();
        auto time_elapsed_copy = time_elapsed;

        while(time_elapsed >= sf::seconds(0.1))
        {
            current_animation_text.setString( current_animation_text.getString() + dialogs_content[current_dialog_id].getString()[current_animation_letter_id]);
            current_animation_letter_id++;
            if(current_animation_letter_id >= dialogs_content[current_dialog_id].getString().getSize())
            {
                current_animation_letter_id = 0;
                current_animation_text.setString("");
                is_animation_running = false;
                animation_clock.stop();
            }

            time_elapsed -= sf::seconds(0.1);
        }

        if(time_elapsed_copy > sf::seconds(0.1))
        {
            Format_text(0, true);
            animation_clock.restart();
        }
    }
}

uint32_t azoya::Dialog_box::Add_dialog_option(const sf::String & content)
{
    dialogs_content.emplace_back(font, content);
    dialogs_content.back().setCharacterSize(50);
    dialogs_content.back().setFillColor( sf::Color::Black );
    dialogs_content.back().setPosition( (box.getPosition() + sf::Vector2f{10, 20}) );

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

void azoya::Dialog_box::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(box, states);

    if(is_animation_running)
    {
        target.draw(current_animation_text);
    }
    else
    {
        target.draw(dialogs_content[current_dialog_id], states);
    }
}

void azoya::Dialog_box::Format_text(uint32_t which, bool animation)
{
    sf::Text line{font};
    sf::Text copy = (animation)? current_animation_text : dialogs_content[ which ];
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

            if( (line_length + word_length + 90) >= (box.getLocalBounds().size.x - 16) )
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

