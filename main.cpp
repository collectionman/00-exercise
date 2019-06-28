/**
* Copyright (c) 2015 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <ComponentFactory.h>
#include <ComponentInterface.h>
#include <ApplicationInterface.h>

void* createComponent(std::string interfaceName) {
    ComponentFactory* componentFactory = new ComponentFactory();
    componentFactory -> setInterfaceName(interfaceName);
    ComponentInterface* component = componentFactory -> 
        createFrom("./" + interfaceName.substr(0, interfaceName.find("Interface")));
    delete componentFactory;
    return (component -> getInstance());
}

int main()
{
    ApplicationInterface* applicationObject = ((ApplicationInterface*) createComponent("ApplicationInterface")); 
    applicationObject -> run();
    ((ComponentInterface*) applicationObject) -> release();

    return 0;
}