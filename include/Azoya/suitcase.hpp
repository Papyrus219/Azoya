#ifndef AZOYA_SUITCASE_HPP
#define AZOYA_SUITCASE_HPP

#include <Azoya/dialogs.hpp>
#include <Azoya/texture_changer.hpp>

namespace azoya
{

class Suitcase
{
public:
    void Init(const std::filesystem::path & path);

    void Click(sf::Vector2f mouse_pos);

    std::optional<Dialog_manager> dialog_manager;

    sf::Texture suitcase_texture{};
    sf::Sprite suitcase_sprite{ suitcase_texture };
private:
    sf::Font font{};
};

}

#endif // AZOYA_SUITCASE_HPP
