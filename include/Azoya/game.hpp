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
    Dialog_box test_box{};
};

}

#endif // AZOYA_GAME_HPP
