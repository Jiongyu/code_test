#ifndef BASE_FSM_H
#define BASE_FSM_H

#include <unordered_map>
namespace basic
{

template<typename status_, typename event_, typename action_>
struct FSM_node
{
    status_ curStatus;
    status_ nextStatus;
    event_ event;
    action_ action;
    void *param;
};

template<typename status_, typename event_, typename action_>
class FSM_manager
{

public:
    FSM_manager(const FSM_manager& copy) = delete;
    FSM_manager& operator=(const FSM_manager& copy) = delete;

    FSM_manager(FSM_manager && move) = delete;
    FSM_manager& operator=(FSM_manager && move) = delete;

    int sent_event(event_ event)
    {
        auto tmp = nodes_.find(event);
        if(tmp != nodes_.end())
        {
            tmp->second->action(tmp->second->param);
            curStatus_ = tmp->second->nextStatus;
            return 0;
        }
        return -1;
    }

    int add_node(const FSM_node<status_, event_, action_>* node)
    {
        nodes_.insert(std::make_pair(node->event, node));
        return 0;
    }

    int set_startStatus(const status_ & status)
    {
        curStatus_ = status;
        return 0;
    }

    FSM_manager(/* args */){nodes_.clear();};
    ~FSM_manager(){};

private:
    status_ curStatus_;
    std::unordered_map<event_, const FSM_node<status_, event_, action_>*>nodes_;
};

} // basic

#endif // BASE_FSM_H