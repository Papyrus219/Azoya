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

    test_box.Init(font, sf::Color::Green, sf::Color::Red);

    dialog1_id = test_box.Add_dialog_option("Hello Gabi! Fajna ta bliblioteka choc, Ma swoje wady. Ale nie ma tragedii...");
    dialog2_id = test_box.Add_dialog_option("Litwo! Ojczyzno moja! ty jestes jak zdrowie Ile cie trzeba cenic, ten tylko sie dowie, Kto cię stracil. Dzis pieknosc twa w calej ozdobie Widze i opisuje, bo tesknie po tobie.");
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
    test_box.Update();

    while(auto event = window.pollEvent())
    {
        if(auto button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(button_pressed->button == sf::Mouse::Button::Left)
            {
                test_box.Set_dialog_option(dialog1_id);
            }
            else if(button_pressed->button == sf::Mouse::Button::Right)
            {
                test_box.Set_dialog_option(dialog2_id);
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

    window.draw( test_box );

    window.display();
}
