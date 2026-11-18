#include <Azoya/dialog_box.hpp>

using namespace azoya;

void azoya::Dialog_box::Init(const sf::Font & font, const sf::String & content, sf::Color background_color, sf::Color border_color)
{
    this->content.setFont(font);
    this->content.setString( content );
    this->content.setCharacterSize( 50 );
    this->content.setFillColor( sf::Color::Black );

    box.setFillColor( background_color );
    box.setOutlineThickness(8);
    box.setOutlineColor(border_color);

    box.setSize({1000, 400});
    box.setPosition({100, 500});

    this->content.setPosition( (box.getPosition() + sf::Vector2f{10, 20}) );

    Format_text();
}

void azoya::Dialog_box::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(box, states);
    target.draw(content, states);
}

void azoya::Dialog_box::Format_text()
{
    sf::Text tmp = content;
    sf::Text copy = content;
    tmp.setString("");
    content.setString("");

    sf::Text word{};

    for(auto c : copy.getString())
    {
        if( (c == ' ') && ( (tmp.getLocalBounds().size.x + 10) >= (box.getLocalBounds().size.x + 16)) )
        {
            content.setString( content.getString() + tmp.getString() + "\n" );

            tmp.setString( tmp.getString() + word );
            tmp.setString("");

        }
        else
        {
        }
    }
}

