#include <iostream>
#include <Azoya/game.hpp>

int main()
{
    azoya::Game game{};

    game.Setup();
    game.Start();

    return 0;
}
