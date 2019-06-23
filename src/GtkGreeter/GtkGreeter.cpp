/**
* Copyright (c) 2015 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <gtk/gtk.h>
#include <string>

#include <GreeterIterface.h>
#include <ComponentInterface.h>

class GtkGreeter : public GreeterInterface, public ComponentInterface
{
    public:
        GtkGreeter();
        virtual ~GtkGreeter();
        void greet(std::string message);

        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        int referenceCounter;
        bool implemented;
};

GtkGreeter::GtkGreeter() : referenceCounter(0){}

GtkGreeter::~GtkGreeter(){}

void GtkGreeter::greet(std::string message)
{
    GtkWidget *window;
    GtkWidget *button;

    gtk_init (NULL, 0);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_signal_connect (GTK_OBJECT (window), "destroy",
                            GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

    gtk_container_border_width (GTK_CONTAINER (window), 10);

    std::string greeting;
    greeting = "I am the gtk greeter and the message is: "+message;
    button = gtk_button_new_with_label (greeting.c_str());

    gtk_container_add (GTK_CONTAINER (window), button);
    gtk_widget_show (button);

    gtk_widget_show (window);

    gtk_main ();
}

//ComponentInterface:
bool GtkGreeter::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "GreeterInterface") ?
        implemented = true
            : implemented = false;
}

void* GtkGreeter::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void GtkGreeter::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new GtkGreeter();
}
