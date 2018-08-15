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

#ifndef BORIS_SYSTEM_BRAIN_CLIENTMESSAGES_H
#define BORIS_SYSTEM_BRAIN_CLIENTMESSAGES_H

#include <cstdio>
#include <cstdlib>
#include <cstring>


class Client_Message {

    public:
        enum {
            header_length = 4
        };
        enum {
            max_body_length = 512
        };

        Client_Message()
                : body_length_(0) {
        }

        const char *data() const {
            return data_;
        }

        char *data() {
            return data_;
        }

        std::size_t length() const {
            return header_length + body_length_;
        }

        const char *body() const {
            return data_ + header_length;
        }

        char *body() {
            return data_ + header_length;
        }

        std::size_t body_length() const {
            return body_length_;
        }

        void body_length(std::size_t new_length) {
            body_length_ = new_length;
            if (body_length_ > max_body_length)
                body_length_ = max_body_length;
        }

        bool decode_header() {
            char header[header_length + 1] = "";
            std::strncat(header, data_, header_length);
            body_length_ = std::atoi(header);
            if (body_length_ > max_body_length) {
                body_length_ = 0;
                return false;
            }
            return true;
        }

        void encode_header() {
            char header[header_length + 1] = "";
            std::sprintf(header, "%4d", body_length_);
            std::memcpy(data_, header, header_length);
        }

    private:
        char data_[header_length + max_body_length];
        std::size_t body_length_;
};



#endif //BORIS_SYSTEM_BRAIN_CLIENTMESSAGES_H
