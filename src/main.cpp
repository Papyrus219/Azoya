#include <iostream>
#include <Azoya/game.hpp>

int main()
{
    std::locale::global(std::locale("C.UTF-8"));
    std::wcout.imbue(std::locale());
    std::wclog.imbue(std::locale());
    std::wcerr.imbue(std::locale());

    azoya::Game game{};

    game.Setup();
    game.Start();

    return 0;
}
