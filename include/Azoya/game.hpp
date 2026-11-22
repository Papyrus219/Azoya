#ifndef AZOYA_GAME_HPP
#define AZOYA_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Azoya/npc.hpp>

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

    uint32_t dialog1_id{};
    uint32_t dialog2_id{};

    sf::Font font{};
    Dialog_box test_box{};

    Input_box test_input_box{};

    Dialog_box * current_dialog_box{};

    Npc test_npc{};
    Npc * current_npc;

    sf::Texture button_texture{};
    sf::Sprite button_sprite{ button_texture };

    sf::Texture background_texture{};
    sf::Sprite background_sprite{background_texture};

    sf::SoundBuffer sound_bufer{};
    sf::Sound sound{ sound_bufer };
};

}

#endif // AZOYA_GAME_HPP
