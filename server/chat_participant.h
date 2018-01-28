//
// Created by zorvalt on 28.01.18.
//

#ifndef PROJECT_CHAT_PARTICIPANT_H
#define PROJECT_CHAT_PARTICIPANT_H


#include <boost/shared_ptr.hpp>
#include "chat_message.hpp"

class chat_participant
{
public:
    virtual ~chat_participant() {}
    virtual void deliver(const chat_message& msg) = 0;
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;


#endif //PROJECT_CHAT_PARTICIPANT_H
