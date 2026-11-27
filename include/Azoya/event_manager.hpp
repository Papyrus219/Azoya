#ifndef AZOYA_EVENT_MANAGER_HPP
#define AZOYA_EVENT_MANAGER_HPP

#include <string_view>

namespace azoya
{

class Event_manager
{
public:
    virtual void Annouce_event(std::wstring_view event_name) = 0;
};

}

#endif // AZOYA_EVENT_MANAGER_HPP
