#include <Azoya/npc.hpp>
#include <Azoya/npc_parser.hpp>

using namespace azoya;

azoya::Npc_parser azoya::Npc::parser{};

void azoya::Npc::Click()
{
    current_dialog_node_id = dialog_graf[ current_dialog_node_id ].next_node_id;

    std::clog << "Dialog: " << current_dialog_node_id << " -> " << dialog_graf[current_dialog_node_id].dialog_text_id << '\n';

    dialog_box.Set_dialog_option( dialog_graf[ current_dialog_node_id ].dialog_text_id );
}
