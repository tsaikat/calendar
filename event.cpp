#include "event.h"

Event::Event (std::string& name, std::string& place, int duration, int participants )
    : mName(name), mPlace(place), mDuration(duration), mParticipants(participants) {}


bool Important::isMoveable () const  { return false;}
bool Optional::isMoveable () const  { return false;}
bool Moveable::isMoveable () const  { return true;}

std::string Important::getType () const  { 
    std::string str = "Important";
    // return "'\033[93mImportant'\033[0m"; // for coloring the out out
    return str;}
std::string Optional::getType () const  { return "Optional";}
std::string Moveable::getType () const  { return "Moveable";}

Important::Important (std::string& name, std::string& place, int duration, int participants) 
    : Event(name, place, duration, participants) {}

Optional::Optional (std::string& name, std::string& place, int duration, int participants) 
    : Event(name, place, duration, participants) {}

Moveable::Moveable (std::string& name, std::string& place, int duration, int participants) 
    : Event(name, place, duration, participants) {}



std::ostream& operator << (std::ostream &out, const Event& event) {
    out <<  std::setfill(' ') << std::setw(20) << event.mName << " |" <<
            std::setfill(' ') << std::setw(20) << event.mPlace << " |" <<
            std::setfill(' ') << std::setw(20) << event.mParticipants << " |" <<
            std::setfill(' ') << std::setw(20) << event.getType() << " |" <<
            std::setfill(' ') << std::setw(19) << event.mDuration <<"h"<< " |" << std::endl;
    return out;
}

std::string Event::getName() const { return mName; }
std::string Event::getPlace() const { return mPlace; }
unsigned Event::getDuration() const { return mDuration; }
unsigned Event::getParticipants() const { return mParticipants; }
