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

#ifndef BORIS_SYSTEM_BRAIN_USERINPUT_SERVER_H
#define BORIS_SYSTEM_BRAIN_USERINPUT_SERVER_H

#include <deque>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "ClientMessages.h"


using boost::asio::ip::tcp;




namespace Boris_Brain {

    typedef std::deque<Client_Message> client_message_queue;

    class Client_Participant
    {
    public:
        virtual ~Client_Participant() {}
        virtual void deliver(const Client_Message& msg) = 0;
    };

    typedef std::shared_ptr<Client_Participant> client_participant_ptr;

    class Client_Room
    {
    public:

        void join(client_participant_ptr participant);

        void leave(client_participant_ptr participant);

        void deliver(const Client_Message& msg);

    private:
        std::set<client_participant_ptr> participants_;
        enum{ MAX_RECENT_MSG = 100};
        client_message_queue recent_msgs_;
    };

    ///----------------------------------------------------------------------///

    class Client_Session : public Client_Participant, public std::enable_shared_from_this<Client_Session>
    {
    public:





    private:
        tcp::socket socket_;
        Client_Room& room_;
    };



} /// End of Boris Brain namespace !



#endif //BORIS_SYSTEM_BRAIN_USERINPUT_SERVER_H
