#ifndef AZOYA_GAME_HPP
#define AZOYA_GAME_HPP

#include <SFML/Graphics.hpp>
#include <Azoya/dialog_box.hpp>

namespace azoya
{

class Game
{
public:
    void Setup();
    void Start();

private:
    void Render();
    void Update();

    sf::RenderWindow window{};

    sf::Font font{};
    sf::Text comunicate{font};
};

}

#endif // AZOYA_GAME_HPP
