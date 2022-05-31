#ifndef __EVENT__
#define __EVENT__


#include <iostream>
#include <string>
#include <iomanip>

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
    virtual bool isMoveable() const = 0;
    /**
     * Gets the name type of event type (pure virtual method)
     * @return the type of Event as string
     */
    virtual std::string getType() const = 0; 
    /// @return member mName
    std::string getName() const;
    /// @return memeber mPlace
    std::string getPlace() const;
    /// @return member mDuration 
    unsigned getDuration() const;
    /// @return memeber mParticipants
    unsigned getParticipants() const;
    
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
    Important (std::string& name, std::string& place, int duration, int participants);
    bool isMoveable() const override;
    std::string getType() const override;
};

/**
 * @class Optional
 * Optional is a derived class from Event. Represent events that are Optional and not moveable
 */
class Optional : public Event {
public:
    Optional (std::string& name, std::string& place, int duration, int participants);
    bool isMoveable() const override;
    std::string getType() const override;    
};

/**
 * @class Moveable
 * Moveable is a derived class from Event. Represent events that are moveable
 */
class Moveable : public Event {
public:
    Moveable (std::string& name, std::string& place, int duration, int participants);
    bool isMoveable() const override;
    std::string getType() const override;
};


#endif
