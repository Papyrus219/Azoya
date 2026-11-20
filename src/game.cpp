#include <Azoya/game.hpp>
#include <iostream>
#include <Azoya/npc.hpp>
#include <Azoya/npc_parser.hpp>

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

    test_npc = Npc::parser.Parse_npc_config_file("../../../data/Piotrek_Gola.pgconf");

    if(!test_npc.texture.loadFromFile("../../../img/button.png"))
    {
        std::cerr << "DOĆ KROTSET!\n";
    }

    test_npc.sprite.setTexture(test_npc.texture, true);
    test_npc.sprite.setPosition({900, 500});

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
    if(current_npc)
    {
        switch(current_npc->Get_mode())
        {
            case Node_mode::NONE:
                break;
            case Node_mode::DIALOG:
                current_npc->dialog_box.Update();
            case Node_mode::INPUT:
                ///@todo
                break;
            case Node_mode::FUNCTION:
                break;
        }
    }

    while(auto event = window.pollEvent())
    {
        if(auto button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(button_pressed->button == sf::Mouse::Button::Left)
            {
                auto raw_pos = sf::Mouse::getPosition( window );
                auto mouse_pos = window.mapPixelToCoords( raw_pos );

                current_npc->Click();
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

    if(current_npc)
    {
        window.draw( current_npc->sprite );

        switch(current_npc->Get_mode())
        {
            case Node_mode::NONE:
                break;
            case Node_mode::DIALOG:
                window.draw( current_npc->dialog_box );
            case Node_mode::INPUT:
                ///@todo
                break;
            case Node_mode::FUNCTION:
                break;
        }
    }

    window.display();
}
