/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef GREETER_INTERFACE_H
#define GREETER_INTERFACE_H

#include <string>

class GreeterInterface
{
    public:
        virtual ~GreeterInterface() {}
        virtual void greet(std::string message) = 0;
};

#endif // GREETER_INTERFACE_H
