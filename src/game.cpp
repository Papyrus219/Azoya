#include <Azoya/game.hpp>
#include <iostream>

using namespace azoya;

void azoya::Game::Setup()
{
    window.create(sf::VideoMode{ {1920, 1080} }, "Azoya", sf::Style::Default);

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

    dialog1_id = test_box.Add_dialog_option("Hello Gabi! Fajna ta bliblioteka choc, Ma swoje wady. Ale nie ma tragedii...");
    dialog2_id = test_box.Add_dialog_option("Litwo! Ojczyzno moja! ty jestes jak zdrowie Ile cie trzeba cenic, ten tylko sie dowie, Kto cie stracil. Dzis pieknosc twa w calej ozdobie Widze i opisuje, bo tesknie po tobie.");

    if(!button_texture.loadFromFile("../../../img/button.png"))
    {
        std::cerr << "DOĆ KROTSET!\n";
    }

    button_sprite.setTexture(button_texture, true);
    button_sprite.setPosition( {900, 500} );
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
    if(current_dialog_box)
    {
        current_dialog_box->Update();
    }

    while(auto event = window.pollEvent())
    {
        if(auto button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(button_pressed->button == sf::Mouse::Button::Left)
            {
                auto raw_pos = sf::Mouse::getPosition( window );
                auto mouse_pos = window.mapPixelToCoords( raw_pos );

                if(button_sprite.getGlobalBounds().contains( mouse_pos ))
                {
                    test_box.Set_dialog_option(dialog1_id);
                    test_box.Set_text_speed( Dialog_box::Text_speed::NORMAL );
                    test_box.Set_background_color( {115, 92, 221} );
                    test_box.Set_outline_color( {114, 0, 179} );
                    test_box.Set_text_color( {55, 0, 10} );

                    current_dialog_box = &test_box;
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
    window.clear( sf::Color::White );

    if(current_dialog_box)
    {
        window.draw( test_box );
    }

    window.draw( button_sprite );

    window.display();
}
