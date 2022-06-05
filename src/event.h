#ifndef __EVENT__
#define __EVENT__


#include <iostream>
#include <string>
#include <iomanip>
#include "datetime.h"

/**
 * @class Event
 * Event is an abstract class that contains the information about the event and methods to interact with them.
 */
class Event {
public:
    /// Constructor to initilize member veriables
    Event (std::string& name, std::string& place, int duration, int participants );
    /// (friend) Overloads << operator and formats events for printing out
    friend std::ostream& operator << (std::ostream &out, const Event& event);
    /**
     * Checks whether a Event is Moveable or not (pure virtual method)
     * @retval true if moveable
     * @retval false if not moveable
     */
    virtual bool isMoveable() const;
    /**
     * Gets the name type of event type (pure virtual method)
     * @return the type of Event as string
     */
    virtual std::string getType() const = 0; 
    /// @return member mName
    std::string getName() const;
    /// @return member mPlace
    std::string getPlace() const;
    /// @return member mDuration 
    unsigned getDuration() const;
    /// @return memeber mParticipants
    unsigned getParticipants() const;
    /// @return additional memeber veriable from the derived class in string format (pure virtual method)
    virtual std::string getExtra() const = 0;
    /**
     * Structure and push events in ostream (pure virtual method)
     * @param out ostream where we push the event
     */
    virtual void print(std::ostream& out) const = 0;
    
protected:
    std::string mName;
    std::string mPlace;
    int mDuration;
    int mParticipants;
};

/**
 * @class Important
 * Important is a derived class from Event. Represent events that are important and not moveable
 */
class Important : public Event {
public:
    Important (std::string& name, std::string& place, int duration, int participants, std::string& reason);
    std::string getType() const override;
    void print(std::ostream& out) const override;
    std::string getExtra() const override;
private:
    /// Reason for being an Important event
    std::string impReason;
};

/**
 * @class Optional
 * Optional is a derived class from Event. Represent events that are Optional and not moveable
 */
class Optional : public Event {
public:
    Optional (std::string& name, std::string& place, int duration, int participants, bool vis);
    std::string getType() const override;
    void print(std::ostream& out) const override;  
    std::string getExtra() const override; 
private:
    /// Should the event be less visible in the calendar? true if Yes
    bool LessVis;
};

/**
 * @class Moveable
 * Moveable is a derived class from Event. Represent events that are moveable
 */
class Moveable : public Event {
public:
    Moveable (std::string& name, std::string& place, int duration, int participants, const DateTime& moveDate);
    bool isMoveable() const override;
    std::string getType() const override;
    void print(std::ostream& out) const override;
    std::string getExtra() const override;
private:
    /// Untill the date the event is allowed to be moved
    DateTime moveUntill;
};


#endif
