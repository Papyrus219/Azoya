#include <Azoya/game.hpp>
#include <iostream>
#include <Azoya/npc.hpp>
#include <Azoya/npc_parser.hpp>

using namespace azoya;

void azoya::Game::Setup()
{
    window.create(sf::VideoMode{ {1910, 1080} }, "Azoya", sf::Style::Default);

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

    test_npc = Npc::parser.Parse_npc_config_file("../../../data/Piotrek_Gola.pgconf");

    if(!test_npc.texture.loadFromFile("../../../img/button.png"))
    {
        std::cerr << "DOĆ KROTSET!\n";
    }

    if(!background_texture.loadFromFile("../../../img/background.png"))
    {
        std::cerr << "NOSZ KURNA!\n";
    }

    background_sprite.setTexture(background_texture, true);

    test_npc.sprite.setTexture(test_npc.texture, true);
    test_npc.sprite.setPosition({900, 500});

    test_npc.dialog_box.Set_size( {1680, 240} );
    test_npc.dialog_box.Set_position( {120, 832} );

    test_npc.dialog_box.Set_text_speed( Dialog_box::Text_speed::FAST );


    current_npc = &test_npc;
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
    auto raw_pos = sf::Mouse::getPosition( window );
    auto mouse_pos = window.mapPixelToCoords( raw_pos );


    if(current_npc)
    {
        switch(current_npc->Get_mode())
        {
            case Node_mode::NONE:
                break;
            case Node_mode::DIALOG:
                current_npc->dialog_box.Update();
                break;
            case Node_mode::INPUT:
                current_npc->input_box.Update( mouse_pos );
                break;
            case Node_mode::FUNCTION:
                break;
        }
    }

    test_input_box.Update(mouse_pos);

    while(auto event = window.pollEvent())
    {
        if(auto button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(button_pressed->button == sf::Mouse::Button::Left)
            {
                if(current_npc)
                {
                    current_npc->Click( mouse_pos );
                }

                auto result = test_input_box.Click( mouse_pos );
                if(result)
                {
                    std::clog << "CLick: " << result.value() << '\n';
                }
            }
            else if(button_pressed->button == sf::Mouse::Button::Right)
            {
                test_box.Set_name("Kunegunda");
            }
        }
        else if(event->is<sf::Event::Closed>())
        {
            std::cout << "Sayonara!\n";
            window.close();
        }
    }
}

void azoya::Game::Render()
{
    window.clear();

    window.draw( background_sprite );

    if(current_npc)
    {
        window.draw( current_npc->sprite );

        switch(current_npc->Get_mode())
        {
            case Node_mode::NONE:
                break;
            case Node_mode::DIALOG:
                window.draw( current_npc->dialog_box );
                break;
            case Node_mode::INPUT:
                window.draw( current_npc->input_box );
                break;
            case Node_mode::FUNCTION:
                break;
        }
    }

    window.display();
}
