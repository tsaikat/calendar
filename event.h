#ifndef __EVENT__
#define __EVENT__


#include <iostream>
#include <string>


class Event {
    public:
    Event (std::string& name, std::string& place, int duration, int participants );
    virtual bool isMovable() const = 0;
    virtual std::string& getType() const = 0; 
    
    protected:
    std::string mName, mPlace;
    int mDuration, mParticipants;
};

class Important : public Event {
    Important (std::string& name, std::string& place, int duration, int participants);
    bool isMovable() const override;
    std::string getType() const override;
};

class Optional : public Event {
    Optional (std::string& name, std::string& place, int duration, int participants);
    bool isMovable() const override;
    std::string getType() const override;    
};

class Moveable : public Event {
    Moveable (std::string& name, std::string& place, int duration, int participants);
    bool isMovable() const override;
    std::string getType() const override;
};


#endif
