#ifndef AZOYA_TEXTURE_CHANGER_HPP
#define AZOYA_TEXTURE_CHANGER_HPP

#include <SFML/Graphics.hpp>

namespace azoya
{

class Texture_changer
{
public:
    void Init(const sf::Texture & texture, sf::Vector2i variant_size);
    sf::IntRect Get_variant_rect(uint8_t variant_number);

private:
    sf::Vector2i texture_size{};
    sf::Vector2i variant_size{};
    uint colums_amount{};
};

}

#endif // MEME_TEXTURE_CHANGER_HPP

