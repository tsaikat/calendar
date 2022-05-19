#ifndef __EVENT__
#define __EVENT__


#include <iostream>
....
#include "time.h"


class Event {
};

class EvImportant : public Event {

};

class EvOptional : public Event {
    
};

class EvMoveable : public Event {
    
};


#endif
