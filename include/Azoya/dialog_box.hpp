#ifndef AZOYA_DIALOG_BOX_HPP
#define AZOYA_DIALOG_BOX_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdint>

namespace azoya
{

class Dialog_box : public sf::Drawable
{
public:
    void Init(const sf::Font & font, sf::Color background_color, sf::Color border_color);

    void Update();

    uint32_t Add_dialog_option(const sf::String & content);
    void Set_dialog_option(uint32_t id);

private:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    void Format_text(uint32_t which, bool animation = false);

    uint32_t current_dialog_id{};

    bool is_animation_running{};

    sf::RectangleShape box{};
    sf::Font font{};

    sf::Clock animation_clock{};
    std::vector<sf::Text> dialogs_content{};

    sf::Text current_animation_text{font};
    uint64_t current_animation_letter_id{};

};

}

#endif // AZOYA_DIALOG BOX_HPP
