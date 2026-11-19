#ifndef AZOYA_DIALOG_NODE
#define AZOYA_DIALOG_NODE

#include <cstdint>

namespace azoya
{

struct Dialog_node
{
    uint32_t dialog_text_id{};
    uint32_t sprite_variant_id{};

    uint32_t next_node_id{};
    bool next_is_input{};
};

}

#endif //AZOYA_DIALOG_NODE
