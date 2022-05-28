#ifndef __EVENT__
#define __EVENT__


#include <iostream>
#include <string>
#include <iomanip>


class Event {
public:
    Event (std::string& name, std::string& place, int duration, int participants );
    virtual bool isMoveable() const = 0;
    virtual std::string getType() const = 0; 
    friend std::ostream& operator << (std::ostream &out, const Event& event);
    std::string getName() const;
    std::string getPlace() const; 
    unsigned getDuration() const;
    
protected:
    std::string mName;
    std::string mPlace;
    int mDuration;
    int mParticipants;
};

class Important : public Event {
public:
    Important (std::string& name, std::string& place, int duration, int participants);
    bool isMoveable() const override;
    std::string getType() const override;
};

class Optional : public Event {
public:
    Optional (std::string& name, std::string& place, int duration, int participants);
    bool isMoveable() const override;
    std::string getType() const override;    
};

class Moveable : public Event {
public:
    Moveable (std::string& name, std::string& place, int duration, int participants);
    bool isMoveable() const override;
    std::string getType() const override;
};


#endif
