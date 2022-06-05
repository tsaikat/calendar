#ifndef __CALENDAR__
#define __CALENDAR__

#include <iostream>
#include <map>
#include <memory>
#include <fstream>
#include <filesystem>
#include "event.h"
#include "datetime.h"

/**
 * @class Calendar
 * Calendar stores events according to their dates in a map and it comes with methods that interact with the events 
 */
class Calendar {
public:
    /**
     * adds events to the calendar
     * @param date date of the event
     * @param event event to be added
     * @return true if it was successful, false otherwise
     */
    bool pushEvent(DateTime date, std::shared_ptr<Event>& event);   
    /**
     * Finds and prints all events between two range of DateTime
     * @param begin start of the DateTime
     * @param end end of the DateTime
     * @return true if any at least one event was found and printed, false if nothing found
     */
    bool printEvents(DateTime& begin, DateTime& end);
    /**
     * Prints all the event on a given day
     * @param dayBegin given day
     */
    void printEvents(DateTime& dayBegin);
    /**
     * Finds event by the name of the event
     * @return true if found, false if not found
     */
    bool findByName(std::string name);
    /**
     * Finds event by the location of the event
     * @return true if found, false if not found
     */
    bool findByPlace(std::string name);
    /**
     * Deletes an event from the calendar
     * @param date event that needs to be deleted in DateTime form
     * @return true if successful, false otherwise
     */
    bool deleteEvent(const DateTime& date);
    /**
     * Finds the next available time in the calendar
     * @param inDate DateTime from when we look for the available time in calendar
     * @param duration duration of the event for which we are looking the free time for
     * @return true when the free time found
     */
    bool printFreeTime(const DateTime& inDate, const unsigned duration);
    /**
     * Checks whether if a DateTime is free for an event of specific duration
     * @param date DateTime to check if it's free
     * @param eventDuration for the period of time we are looking for the free spot 
     * @return true if free, false if not free
     */
    bool isTimeFree (const DateTime& date, unsigned eventDuration);
    /**
     * Moves a moveable event from one DateTime to another DateTime
     * @param moveFrom from this date and time
     * @param moveTo to this date and time
     * @return true if move was successful, false otherwise
     */
    bool moveEvent (const DateTime& moveFrom, const DateTime& moveTo );
    /**
     * throws a message on the console display and waits for pressing enter
     * @param msg string to throw
     */
    void throwMsg (const std::string& msg) const;
    /**
     * Exports all events in CSV format
     * @return the path of exported .csv file
     */
    std::string exportCSV();
    /**
     * Exports all events in HTML format
     * @return the path of exported .html file
     */
    std::string exportHTML();
    ///Imports events to calendar from CSV file
    void importCSV();
    /**
     * Asks user to input a file path/name. Checks whether the file exist or not
     * @return if the file exist returns the name/path
     */
    std::string getFileName() const;

private:
    /// STL container map to store DateTime as a key and Event as value
    std::map <DateTime, std::shared_ptr<Event>> database;
};


#endif