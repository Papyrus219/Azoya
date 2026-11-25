#include "Azoya/suitcase.hpp"
#include <fstream>

void azoya::Suitcase::Init(const std::filesystem::path & path)
{
    std::ifstream file{path};
    if(!file)
    {

    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    std::string buffor = ss.str();

    size_t pos{0};
    dialog_manager = Dialog_manager::parser.Parse(buffor, pos);
}
