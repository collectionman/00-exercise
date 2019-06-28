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

void* createComponent(std::string interfaceName) {
    ComponentFactory* componentFactory = new ComponentFactory();
    componentFactory -> setInterfaceName(interfaceName);
    ComponentInterface* component = componentFactory -> 
        createFrom("./" + interfaceName.substr(0, interfaceName.find("Interface")));
    delete componentFactory;
    return (component -> getInstance());
}

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

Application::Application() : referenceCounter(0){
    std::cout << "Application Created" << std::endl;
}

Application::~Application(){
    std::cout << "Application Deleted" << std::endl;
}

int Application::run()
{
    MessengerInterface* messengerObject = ((MessengerInterface*) createComponent("MessengerInterface"));    
    GreeterInterface* greeterObject = ((GreeterInterface*) createComponent("GreeterInterface"));

    greeterObject->greet(messengerObject->say());

    ((ComponentInterface*) greeterObject) -> release();
    ((ComponentInterface*) messengerObject) -> release();

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
