#ifndef AZOYA_INPUT_BOX_HPP
#define AZOYA_INPUT_BOX_HPP

#include <SFML/Graphics.hpp>
#include <optional>

namespace azoya
{

class Input_box: public sf::Drawable
{
public:
    enum class Hover_type
    {
        LIGHT,
        DARK
    } hover_type;

    void Init(const sf::Font & font, sf::Color background_color, sf::Color border_color, Hover_type hover_type = Hover_type::LIGHT);
    void Update(sf::Vector2f mouse_pos);

    uint32_t Add_option_pack(const sf::String & text_1, const sf::String & text_2, uint32_t result_1, uint32_t result_2);
    void Set_option_pack(uint32_t pack_id);

    std::optional<uint32_t> Click(sf::Vector2f mouse_pos);

    void Set_background_color(sf::Color new_color);
    void Set_outline_color(sf::Color new_color);
    void Set_text_color(sf::Color new_color);

private:
    struct Option_pack
    {
        Option_pack(const sf::Font & font);

        sf::Text text_1;
        sf::Text text_2;

        uint32_t result_1{};
        uint32_t result_2{};
    };

    virtual void draw(sf::RenderTarget & target, sf::RenderStates strates) const override;

    sf::Font font{};

    std::vector<Option_pack> options_packs{};

    uint32_t current_option_id{};

    sf::RectangleShape main_box{};
    sf::RectangleShape option_1_box{};
    sf::RectangleShape option_2_box{};

    sf::Color background_color{};
    sf::Color text_color{};
};

}

#endif // AZOYA_INPUT_BOX_HPP
