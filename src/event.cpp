#include "event.h"

Event::Event (std::string& name, std::string& place, int duration, int participants )
    : mName(name), mPlace(place), mDuration(duration), mParticipants(participants) {}

Important::Important (std::string& name, std::string& place, int duration, int participants, std::string& reason) 
    : Event(name, place, duration, participants), impReason(reason) {}

Optional::Optional (std::string& name, std::string& place, int duration, int participants, bool vis) 
    : Event(name, place, duration, participants), LessVis(vis) {}

Moveable::Moveable (std::string& name, std::string& place, int duration, int participants, const DateTime& moveDate) 
    : Event(name, place, duration, participants), moveUntill(moveDate) {}

std::ostream& operator << (std::ostream &out, const Event& event) {
    event.print(out);
    return out;
}

std::string Event::getName() const { return mName; }
std::string Event::getPlace() const { return mPlace; }
unsigned Event::getDuration() const { return mDuration; }
unsigned Event::getParticipants() const { return mParticipants; }

bool Event::isMoveable () const  { return false;}
bool Moveable::isMoveable () const  { 
    return (moveUntill.currDateTime() < moveUntill);
}

std::string Important::getType () const  { return "Important";}
std::string Optional::getType () const  { return "Optional";}
std::string Moveable::getType () const  { return "Moveable";}



std::string Important::getExtra() const { return impReason; }
std::string Optional::getExtra() const { return std::to_string(LessVis); }
std::string Moveable::getExtra() const { return moveUntill.getDate(); }


void Important::print(std::ostream& out) const {
    out <<  std::setfill(' ') << std::setw(28) << mName << " |" <<
            std::setfill(' ') << std::setw(20) << mPlace << " |" <<
            std::setfill(' ') << std::setw(18) << mParticipants << " |" << "\33[41m" <<
            std::setfill(' ') << std::setw(20) << impReason << " - (I)\33[0m |" <<
            std::setfill(' ') << std::setw(15) << mDuration <<"h" << " |" << std::endl;
}

void Optional::print(std::ostream& out) const {
    if (LessVis) out << "\33[90m";
    out <<  std::setfill(' ') << std::setw(28) << mName << " |" <<
            std::setfill(' ') << std::setw(20) << mPlace << " |" <<
            std::setfill(' ') << std::setw(18) << mParticipants << " |" <<
            std::setfill(' ') << std::setw(26) << "Optional"<< " |" <<
            std::setfill(' ') << std::setw(15) << mDuration <<"h" << " |";
    if (LessVis) out <<  "\33[0m";
    out << std::endl;
}

void Moveable::print(std::ostream& out) const {
    out <<  std::setfill(' ') << std::setw(28) << mName << " |" <<
            std::setfill(' ') << std::setw(20) << mPlace << " |" <<
            std::setfill(' ') << std::setw(18) << mParticipants << " |" <<
            std::setfill(' ') << std::setw(16) << "Moveable till "<< moveUntill.getDate() << " |" <<
            std::setfill(' ') << std::setw(15) << mDuration <<"h" << " |" << std::endl;
}