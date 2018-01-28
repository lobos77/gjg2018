//
// Created by zorvalt on 28.01.18.
//

#ifndef PROJECT_CHAT_ROOM_H
#define PROJECT_CHAT_ROOM_H


#include <boost/bind.hpp>
#include <set>
#include <deque>
#include "chat_participant.h"
#include "chat_message.hpp"

typedef std::deque<chat_message> chat_message_queue;

class chat_room
{
public:
  void join(chat_participant_ptr participant)
  {
    participants_.insert(participant);
    std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
        boost::bind(&chat_participant::deliver, participant, _1));
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
  }

  void deliver(const chat_message& msg)
  {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    std::for_each(participants_.begin(), participants_.end(),
        boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
  }

private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
};


#endif //PROJECT_CHAT_ROOM_H
