#include <Azoya/game.hpp>
#include <iostream>

using namespace azoya;

void azoya::Game::Setup()
{
    window.create(sf::VideoMode{ {1920, 1080} }, "Azoya", sf::Style::Default, sf::State::Fullscreen);

    if(!font.openFromFile( "../../../fonts/Kotek.otf" ) )
    {
        std::cerr << "KUŹWA MAĆ!\n";
    }

    test_box.Init(font, "Hello Gabi! Fajna ta bliblioteka choc, Ma swoje wady. Ale nie ma tragedii... ALDSK ADJF USHF DSI HF DIUSG HG DUIHFD IUS HDF UOHDFSU HSFDI UFDHFD HFDS IUH HUS UAHF UFHU FH IAD FIDF HJ", sf::Color::Green, sf::Color::Red);

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
    while(auto event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
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
