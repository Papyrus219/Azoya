#ifndef AZOYA_DIALOG_NODE
#define AZOYA_DIALOG_NODE

#include <cstdint>

namespace azoya
{

enum class Node_mode
{
    NONE,
    DIALOG,
    INPUT,
    FUNCTION
};

struct Dialog_node
{
    uint32_t dialog_text_id{};
    uint32_t sprite_variant_id{};
    Node_mode node_mode{};

    Node_mode next_node_mode{};
    uint32_t next_node_id{};
};

}

#endif //AZOYA_DIALOG_NODE
