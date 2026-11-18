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

    comunicate.setPosition( {1700, 500} );
    comunicate.setCharacterSize( 100 );
    comunicate.setFillColor( sf::Color::Black );
    comunicate.setString( "Cool czcionka!" );

    std::cerr << sf::Texture::getMaximumSize() << '\n';
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

    window.draw( comunicate );

    window.display();
}
