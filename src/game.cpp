#include <Azoya/game.hpp>
#include <iostream>
#include <Azoya/npc.hpp>
#include <Azoya/npc_parser.hpp>

using namespace azoya;

void azoya::Game::Setup()
{
    window.create(sf::VideoMode{ {1910, 1080} }, "Azoya", sf::Style::Default);

    if(!Npc::world_texture.loadFromFile("../../../img/world_sprites.png"))
    {
        std::cerr << "Ajajaj!\n";
    }

    if(!font.openFromFile( "../../../fonts/Kotek.otf" ) )
    {
        std::cerr << "KUŹWA MAĆ!\n";
    }
    if(!sound_bufer.loadFromFile("../../../audio/litera.wav"))
    {
        std::cerr << "KURKA WODNA!\n";
    }

    sound.setBuffer( sound_bufer );

    test_box.Init("Adrian", font, sf::Color::Green, sf::Color::Red, sound);

    cowboy_npc = Npc::parser.Parse_npc_config_file("../../../data/cowboy.pgconf");
    mother_npc = Npc::parser.Parse_npc_config_file("../../../data/mother.pgconf");
    superstar_npc = Npc::parser.Parse_npc_config_file("../../../data/superstar.pgconf");
    super_fan_npc = Npc::parser.Parse_npc_config_file("../../../data/super_fan.pgconf");

    active_npcs[0] = &cowboy_npc;
    active_npcs[1] = &mother_npc;
    active_npcs[2] = &superstar_npc;
    active_npcs[3] = &super_fan_npc;

    cowboy_npc.world_sprite.setPosition({300, 400});
    mother_npc.world_sprite.setPosition({550, 400});
    superstar_npc.world_sprite.setPosition({800, 400});
    super_fan_npc.world_sprite.setPosition({1050, 400});

    if(!main_menu_bg_texture.loadFromFile("../../../img/main_menu.png"))
    {
        std::cerr << "MOTYLA NOGA!\n";
    }

    main_menu_bg_sprite.setTexture(main_menu_bg_texture, true);

    if(!start_button_texture.loadFromFile("../../../img/start_button.png"))
    {
        std::cerr << "A NIECH MIE KULE BIJĄ!\n";
    }

    start_button_sprite.setTexture(start_button_texture, true);
    start_button_sprite.setPosition( {560, 700} );

    if(!background_texture.loadFromFile("../../../img/background.png"))
    {
        std::cerr << "NOSZ KURNA!\n";
    }

    background_sprite.setTexture(background_texture, true);

    //Cowboy setup
    cowboy_npc.dialog_sprite.setPosition({900, 500});

    cowboy_npc.dialog_box.Set_size( {1680, 240} );
    cowboy_npc.dialog_box.Set_position( {120, 832} );

    cowboy_npc.dialog_box.Set_text_speed( Dialog_box::Text_speed::FAST );

    //Mother setup
    mother_npc.dialog_sprite.setPosition({900, 500});

    mother_npc.dialog_box.Set_size( {1680, 240} );
    mother_npc.dialog_box.Set_position( {120, 832} );

    mother_npc.dialog_box.Set_text_speed( Dialog_box::Text_speed::FAST );

    //Superstar setup
    superstar_npc.dialog_sprite.setPosition({900, 500});

    superstar_npc.dialog_box.Set_size( {1680, 240} );
    superstar_npc.dialog_box.Set_position( {120, 832} );

    superstar_npc.dialog_box.Set_text_speed( Dialog_box::Text_speed::FAST );

    //Super fan setup
    super_fan_npc.dialog_sprite.setPosition({900, 500});

    super_fan_npc.dialog_box.Set_size( {1680, 240} );
    super_fan_npc.dialog_box.Set_position( {120, 832} );

    super_fan_npc.dialog_box.Set_text_speed( Dialog_box::Text_speed::FAST );
}

void azoya::Game::Start()
{
    while(window.isOpen())
    {
        Render();

        Update();
    }
}

void azoya::Game::Update()
{
    switch(game_state)
    {
        case Game_state::MAIN_MENU:
            Update_main_menu();
            break;
        case Game_state::GAME:
            Update_game();
            break;
        case Game_state::ENDING:
            Update_ending();
            break;
    }

    while(auto event = window.pollEvent())
    {
        switch(game_state)
        {
            case Game_state::MAIN_MENU:
                React_to_event_main_menu( *event );
                break;
            case Game_state::GAME:
                React_to_event_game( *event );
                break;
            case Game_state::ENDING:
                React_to_event_ending( *event );
                break;
        }

        if(event->is<sf::Event::Closed>())
        {
            std::clog << "Sayonara!\n";
            window.close();
        }
    }
}

void azoya::Game::Render()
{
    window.clear();

    switch(game_state)
    {
        case Game_state::MAIN_MENU:
            Render_main_menu();
            break;
        case Game_state::GAME:
            Render_game();
            break;
        case Game_state::ENDING:
            Render_ending();
            break;
    }

    window.display();
}

void azoya::Game::Update_main_menu()
{
    auto raw_pos = sf::Mouse::getPosition( window );
    auto mouse_pos = window.mapPixelToCoords( raw_pos );

    if(start_button_sprite.getGlobalBounds().contains(mouse_pos))
    {
        start_button_sprite.setColor( {100, 100, 100} );
    }
    else
    {
        start_button_sprite.setColor( {255, 255, 255} );
    }
}

void azoya::Game::React_to_event_main_menu(const sf::Event & event)
{
    if(auto button_pressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        auto raw_pos = sf::Mouse::getPosition( window );
        auto mouse_pos = window.mapPixelToCoords( raw_pos );

        if(button_pressed->button == sf::Mouse::Button::Left)
        {
            if(start_button_sprite.getGlobalBounds().contains(mouse_pos))
            {
                game_state = Game_state::GAME;
            }
        }
    }
}

void azoya::Game::Render_main_menu()
{
    window.draw( main_menu_bg_sprite );
    window.draw( start_button_sprite );
}

void azoya::Game::Update_game()
{
    auto raw_pos = sf::Mouse::getPosition( window );
    auto mouse_pos = window.mapPixelToCoords( raw_pos );

    if(current_talking_npc)
    {
        switch(current_talking_npc->Get_mode())
        {
            case Node_mode::NONE:
                current_talking_npc = nullptr;
                break;
            case Node_mode::DIALOG:
                current_talking_npc->dialog_box.Update();
                break;
            case Node_mode::INPUT:
                current_talking_npc->input_box.Update( mouse_pos );
                break;
            case Node_mode::FUNCTION:
                break;
        }
    }

    test_input_box.Update(mouse_pos);
}

void azoya::Game::React_to_event_game(const sf::Event & event)
{
    if(auto button_pressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        auto raw_pos = sf::Mouse::getPosition( window );
        auto mouse_pos = window.mapPixelToCoords( raw_pos );

        if(button_pressed->button == sf::Mouse::Button::Left)
        {
            if(current_talking_npc)
            {
                current_talking_npc->Click( mouse_pos );
            }
            else
            {
                for(auto npc_ptr : active_npcs)
                {
                    if(npc_ptr)
                    {
                        if(npc_ptr->world_sprite.getGlobalBounds().contains(mouse_pos))
                        {
                            current_talking_npc = npc_ptr;
                            current_talking_npc->Click(mouse_pos);
                        }
                    }
                }
            }

            auto result = test_input_box.Click( mouse_pos );
            if(result)
            {
                std::clog << "CLick: " << result.value() << '\n';
            }
        }
    }
}

void azoya::Game::Render_game()
{
    window.draw( background_sprite );

    if(current_talking_npc)
    {
        window.draw( current_talking_npc->dialog_sprite );

        switch(current_talking_npc->Get_mode())
        {
            case Node_mode::NONE:
                break;
            case Node_mode::DIALOG:
                window.draw( current_talking_npc->dialog_box );
                break;
            case Node_mode::INPUT:
                window.draw( current_talking_npc->input_box );
                break;
            case Node_mode::FUNCTION:
                break;
        }
    }
    else
    {
        for(auto npc_ptr : active_npcs)
        {
            if(npc_ptr)
            {
                window.draw( npc_ptr->world_sprite );
            }
        }
    }
}

void azoya::Game::Update_ending()
{

}

void azoya::Game::React_to_event_ending(const sf::Event& event)
{

}

void azoya::Game::Render_ending()
{

}

