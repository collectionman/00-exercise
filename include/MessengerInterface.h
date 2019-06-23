/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef MESSENGER_INTERFACE_H
#define MESSENGER_INTERFACE_H

#include <string>

class MessengerInterface
{
    public:
        virtual ~MessengerInterface() {}
        virtual std::string say() = 0;
};


#endif // MESSENGER_INTERFACE_H
