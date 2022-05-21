#include "event.h"

Event::Event (std::string& name, std::string& place, int duration, int type, int participants )
    : mName(name), mPlace(place), mDuration(duration), mType(type), mParticipants(participants) {}


bool Important::isMovable () const override { return false;}
bool Optional::isMovable () const override { return false;}
bool Moveable::isMovable () const override { return true;}

std::string Important::printType () const override { return "Important";}
std::string Optional::printType () const override { return "Optional";}
std::string Moveable::printType () const override { return "Moveable";}

Important::Important (std::string& name, std::string& place, int duration, int participants) 
    : Event(name, place, duration, participants) {}

Optional::Optional (std::string& name, std::string& place, int duration, int participants) 
    : Event(name, place, duration, participants) {}

Moveable::Moveable (std::string& name, std::string& place, int duration, int participants) 
    : Event(name, place, duration, participants) {}