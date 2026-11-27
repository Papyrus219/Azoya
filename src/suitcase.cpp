#include "Azoya/suitcase.hpp"
#include <fstream>

void azoya::Suitcase::Init(const std::filesystem::path & path)
{
    std::wifstream file;
    file.imbue(std::locale("C.UTF-8"));
    file.open(path);
    if(!file)
    {
        std::cerr << "FAIL TO OPEN FILE!\n";
    }

    std::wostringstream ss{};
    ss << file.rdbuf();

    std::wstring buffor = ss.str();

    size_t pos{0};
    dialog_manager = Dialog_manager::parser.Parse(buffor, pos);
}
