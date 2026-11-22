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
    enum class Game_state
    {
        MAIN_MENU,
        GAME,
        ENDING,
    } game_state{};

    void Render();
    void Update();

    void Render_main_menu();
    void Render_game();
    void Render_ending();

    void Update_main_menu();
    void React_to_event_main_menu(const sf::Event & event);

    void Update_game();
    void React_to_event_game(const sf::Event & event);

    void Update_ending();
    void React_to_event_ending(const sf::Event & event);

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

    sf::Texture main_menu_bg_texture{};
    sf::Sprite main_menu_bg_sprite{ main_menu_bg_texture };

    sf::Texture start_button_texture{};
    sf::Sprite start_button_sprite{ start_button_texture };

    sf::Texture background_texture{};
    sf::Sprite background_sprite{background_texture};

    sf::SoundBuffer sound_bufer{};
    sf::Sound sound{ sound_bufer };
};

}

#endif // AZOYA_GAME_HPP
