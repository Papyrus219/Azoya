#ifndef AZOYA_GAME_HPP
#define AZOYA_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Azoya/npc.hpp>
#include <Azoya/suitcase.hpp>
#include <array>

namespace azoya
{

class Game
{
public:
    void Setup();
    void Start();

private:
    enum class Program_state
    {
        MAIN_MENU,
        GAME,
        ENDING,
    } program_state{};

    enum class Game_state
    {
        NONE,
        DIALOG,
        SUITCASE,
    } game_state;

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

    Dialog_box * current_dialog_box{};

    Npc * current_talking_npc;
    std::array<Npc *, 4> active_npcs{};

    Npc cowboy_npc{};
    Npc mother_npc{};
    Npc super_fan_npc{};
    Npc sus_npc{};
    Npc superstar_npc{};
    Npc tourist_npc{};
    Npc elder_npc{};

    sf::Texture button_texture{};
    sf::Sprite button_sprite{ button_texture };

    sf::Texture main_menu_bg_texture{};
    sf::Sprite main_menu_bg_sprite{ main_menu_bg_texture };

    sf::Texture start_button_texture{};
    sf::Sprite start_button_sprite{ start_button_texture };

    sf::Texture background_texture{};
    sf::Sprite background_sprite{background_texture};

    sf::Texture suitcase_icons_textures{};
    sf::Sprite suitcase_sprite{suitcase_icons_textures};

    Suitcase suitcase{};

    sf::Texture npc_world_texture{};

    sf::SoundBuffer sound_bufer{};
    sf::Sound sound{ sound_bufer };
};

}

#endif // AZOYA_GAME_HPP
