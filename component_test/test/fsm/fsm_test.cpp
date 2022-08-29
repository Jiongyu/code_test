#include "FSM.hpp"
#include <functional>
#include <iostream>
#include <chrono>
#include <thread>

/* define status */
enum Status
{
    status_1 = 0,
    status_2,
    status_3,
    status_4,
};

/* define event */
enum Event
{
    event_1 = 0,
    event_2,
    event_3,
    event_4,
    event_end
};

/* define action */
typedef std::function<void(void*)> Action;

void action1(void* args)
{
    std::cout << "action1 "  << std::endl;
}

void action2(void* args)
{
    std::cout << "action2 "  << std::endl;
}

void action3(void* args)
{
    std::cout << "action3 "  << std::endl;
}

void action4(void* args)
{
    std::cout << "action4 "  << std::endl;
}



int main(int argc, char const *argv[])
{

    /* define node */
    basic::FSM_node<Status, Event, Action>node1 = 
        {status_1, status_2, event_1, action1, nullptr};

    basic::FSM_node<Status, Event, Action>node2 = 
        {status_2, status_3, event_2, action2, nullptr};

    basic::FSM_node<Status, Event, Action>node3 = 
        {status_3, status_4, event_3, action3, nullptr};

    basic::FSM_node<Status, Event, Action>node4 = 
        {status_4, status_1, event_4, action4, nullptr};

    /*define node manager*/
    basic::FSM_manager<Status, Event, Action>manager;
    manager.add_node(&node1);
    manager.add_node(&node2);
    manager.add_node(&node3);
    manager.add_node(&node4);

    /*set start status*/
    manager.set_startStatus(status_1);

    int index = 0;
    while(1)
    {
        manager.sent_event((Event)(index % (event_end)));
        index ++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
