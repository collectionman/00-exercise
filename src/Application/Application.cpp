/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <string>
#include <ComponentFactory.h>
#include <ApplicationInterface.h>
#include <ComponentInterface.h>
#include <GreeterIterface.h>
#include <MessengerInterface.h>

class Application : public ApplicationInterface, public ComponentInterface
{
    public:
        Application();
        virtual ~Application();
        int run();

        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        int referenceCounter;
        bool implemented;
};

Application::Application() : referenceCounter(0){}

Application::~Application(){}

int Application::run()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();

    componentFactoryObject->setInterfaceName("MessengerInterface");
    ComponentInterface* messengerComponent = componentFactoryObject->createFrom("./Messenger");
    MessengerInterface* messengerObject = ( (MessengerInterface*) messengerComponent->getInstance() );

    componentFactoryObject->setInterfaceName("GreeterInterface");
    ComponentInterface* greeterComponent = componentFactoryObject->createFrom("./Greeter");
    GreeterInterface* greeterObject = ( (GreeterInterface*) greeterComponent->getInstance() );

    greeterObject->greet(messengerObject->say());
    greeterComponent->release();
    messengerComponent->release();

    delete componentFactoryObject;

    return 0;
}

//ComponentInterface:
bool Application::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ApplicationInterface") ?
        implemented = true
            : implemented = false;
}

void* Application::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void Application::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new Application;
}
