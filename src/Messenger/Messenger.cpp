#include <iostream>
#include <string>
#include <MessengerInterface.h>
#include <ComponentInterface.h>

class Messenger : public MessengerInterface, public ComponentInterface
{
    public:
        Messenger();
        virtual ~Messenger();
        std::string say( void );

        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        int referenceCounter;
        bool implemented;
};

Messenger::Messenger() : referenceCounter(0){}

Messenger::~Messenger(){}

std::string Messenger::say( void )
{
    return "I can be more than just a message on the console" ;
}

//ComponentInterface:
bool Messenger::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "MessengerInterface") ?
        implemented = true
            : implemented = false;
}

void* Messenger::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void Messenger::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new Messenger();
}