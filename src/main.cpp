#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window{sf::VideoMode{ {1200, 1000} }, "Azoya"};

    sf::Font font{};

    if(!font.openFromFile( "../../../fonts/Kotek.otf" ) )
    {
        std::cerr << "KUŹWA MAĆ!\n";
    }


    sf::Text comunicate{font};
    comunicate.setPosition( {400, 500} );
    comunicate.setCharacterSize( 100 );
    comunicate.setFillColor( sf::Color::Black );
    comunicate.setString( "Cool czcionka!" );

    while(window.isOpen())
    {
        window.clear( sf::Color::White );

        window.draw( comunicate );

        window.display();

        while(auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                std::cout << "Sayonara!\n";
                window.close();
            }
        }
    }

    return 0;
}
