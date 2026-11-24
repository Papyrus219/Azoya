#ifndef AZOYA_DIALOG_BOX_HPP
#define AZOYA_DIALOG_BOX_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdint>
#include <optional>
#include <functional>

namespace azoya
{

class Dialog_box : public sf::Drawable
{
public:
    void Init(const sf::String & name, const sf::Font & font, sf::Color background_color, sf::Color border_color, bool is_enable_name = true, std::optional<std::reference_wrapper<sf::Sound>> letter_sound = {});

    void Update();

    uint32_t Add_dialog_option(const sf::String & content);
    void Set_dialog_option(uint32_t id);

    void Set_name(const sf::String & name);

    enum class Text_speed{SLOW, NORMAL, FAST};
    void Set_text_speed(Text_speed speed);

    void Set_position(sf::Vector2f new_position);
    void Set_size(sf::Vector2f new_size);

    void Set_background_color(sf::Color new_color);
    void Set_outline_color(sf::Color new_color);
    void Set_text_color(sf::Color new_color);

    void Set_character_size( uint16_t new_size );

private:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    void Unformat_text(uint32_t which);
    void Format_text(uint32_t which);

    uint32_t current_dialog_id{};

    bool is_animation_running{};
    bool is_name_enabled{};

    sf::RectangleShape box{};
    sf::RectangleShape name_box{};
    sf::Font font{};

    sf::Text name{font};

    sf::Clock animation_clock{};
    sf::Time letter_apperence_durration{ sf::seconds(0.1) };
    std::vector<sf::Text> dialogs_content{};

    sf::Text current_animation_text{font};
    uint64_t current_animation_letter_id{};

    std::optional<std::reference_wrapper<sf::Sound>> letter_sound{};
};

}

#endif // AZOYA_DIALOG BOX_HPP
