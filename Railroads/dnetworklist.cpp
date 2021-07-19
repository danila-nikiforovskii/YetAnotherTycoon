#include "dnetworklist.h"
#include <QDebug>

DNetworkList::DNetworkList()
{

}

void DNetworkListElement::erase()
{

    DNetworkListElement* prevnode = this->prev;

    if (prevnode!=nullptr)
    {
          //not the first element....
       if (this->next == nullptr)
           {
               prevnode->next = nullptr;

               list->last = prevnode;
           }
       else
           {
               prevnode->next = this->next;

            next->prev = prevnode;
          }

    }
    else
    {
        //the first element
        DNetworkListElement* nextnode = this->next;

        if (nextnode!=nullptr)
            {

                this->list->first = nextnode;
                nextnode->prev = nullptr;
            }
        else
            {
                //the only element...

                this->list->first = nullptr;
                this->list->last = nullptr;
            }




    }

    delete this;

}

DNetworkList::~DNetworkList()
{
//destruction

    DNetworkListElement * dead = last;
    DNetworkListElement * awaiting;

    while (dead!=nullptr)
        {
            awaiting = dead->prev;
            delete dead;
            dead = awaiting;
        }
}

DNetworkListElement::~DNetworkListElement()
{
//destruction
}

DNetworkListElement::DNetworkListElement()
{
//construction
}




void DNetworkList::append(DNetworkListElement * newbie)
{
if (last!=nullptr)
    {
            last -> next = newbie;


            newbie->prev = last;
            newbie->next = nullptr;

            newbie->list = this;

            this->last = newbie;

    }
if (first == nullptr)
    {
        first = newbie;
        newbie->prev = nullptr;
        newbie->next = nullptr;
        newbie->list = this;
        last = newbie;

    }


}

// ======================================= ELEMENTS ===========================


