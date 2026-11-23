#ifndef AZOYA_INPUT_BOX_HPP
#define AZOYA_INPUT_BOX_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <initializer_list>

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

    uint32_t Add_option_pack(std::initializer_list<std::string_view> texts, std::initializer_list<uint32_t> results);
    void Set_option_pack(uint32_t pack_id);

    std::optional<uint32_t> Click(sf::Vector2f mouse_pos);

    void Set_background_color(sf::Color new_color);
    void Set_outline_color(sf::Color new_color);
    void Set_text_color(sf::Color new_color);

private:
    struct Option_pack
    {
        std::vector<sf::Text> texts{};
        std::vector<uint32_t> results{};
        std::vector<sf::RectangleShape> boxes{};
    };

    virtual void draw(sf::RenderTarget & target, sf::RenderStates strates) const override;

    sf::Font font{};

    std::vector<Option_pack> options_packs{};

    uint32_t current_option_id{};

    sf::RectangleShape main_box{};

    sf::Color background_color{};
    sf::Color border_color{};
    sf::Color text_color{};
};

}

#endif // AZOYA_INPUT_BOX_HPP
