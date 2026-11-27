#ifndef AZOYA_DIALOG_COLOR_SET_HPP
#define AZOYA_DIALOG_COLOR_SET_HPP

#include <SFML/Graphics/Color.hpp>

namespace azoya
{

struct Dialog_color_set
{
    sf::Color dialog_bg_color{};
    sf::Color dialog_border_color{};
    sf::Color dialog_text_color{};

    sf::Color input_bg_color{};
    sf::Color input_border_color{};
    sf::Color input_text_color{};
};

}

#endif //AZOYA_DIALOG_COLOR_SET_HPP
