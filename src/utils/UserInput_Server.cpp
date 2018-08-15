/*
 *
 * ____             _        _____           _
 *|  _ \           (_)      / ____|         | |
 *| |_) | ___  _ __ _ ___  | (___  _   _ ___| |_ ___ _ __ ___
 *|  _ < / _ \| '__| / __|  \___ \| | | / __| __/ _ \ '_ ` _ \
 *| |_) | (_) | |  | \__ \  ____) | |_| \__ \ ||  __/ | | | | |
 *|____/ \___/|_|  |_|___/ |_____/ \__, |___/\__\___|_| |_| |_| 2018
 *                                  __/ |
 *                                 |___/
 *
 *                     © Charles200000
*/



#include "UserInput_Server.h"


using boost::asio::ip::tcp;

void Boris_Brain::Client_Room::join(Boris_Brain::client_participant_ptr participant)
{
    participants_.insert(participant);
    for (auto msg: recent_msgs_)
        participant->deliver(msg);
}

void Boris_Brain::Client_Room::leave(Boris_Brain::client_participant_ptr participant)
{
    participants_.erase(participant);
}

void Boris_Brain::Client_Room::deliver(const Client_Message &msg)
{
    recent_msgs_.push_back(msg);

    while (recent_msgs_.size() > MAX_RECENT_MSG)
    {
        recent_msgs_.pop_front();
    }

    for (auto participant: participants_)
        participant->deliver(msg);
}
