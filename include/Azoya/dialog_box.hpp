#ifndef AZOYA_DIALOG_BOX_HPP
#define AZOYA_DIALOG_BOX_HPP

#include <SFML/Graphics.hpp>

namespace azoya
{

class Dialog_box : public sf::Drawable
{
public:
    void Init(const sf::Font & font, const sf::String & content, sf::Color background_color, sf::Color border_color);

private:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    void Format_text();

    sf::RectangleShape box{};
    sf::Font tmp{};
    sf::Text content{tmp};
};

}

#endif // AZOYA_DIALOG BOX_HPP
