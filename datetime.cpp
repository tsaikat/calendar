#include "datetime.h"

DateTime::DateTime(const unsigned& year, const unsigned& month, const unsigned& day, const unsigned& time ) 
: mYear(year), mMonth(month), mDay(day), mTime(time) {}

DateTime::DateTime(const DateTime &other) 
: mYear(other.mYear), mMonth(other.mMonth), mDay(other.mDay), mTime(other.mTime) {}

DateTime::DateTime(){}

bool DateTime::isValid () const {
    unsigned monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(mYear) ) monthDays[1] = 29;
    if ( mDay > monthDays[mMonth-1]  || mDay < 1 || mMonth > 12 || mMonth < 1 ) return false;
    return true;
}

bool DateTime::isLeapYear (unsigned year) const {
    return (( (year % 4 == 0) && (year % 100 != 0) ) || ((year % 400 == 0) && (year % 4000 != 0) )); 
}

bool operator < ( const DateTime& lhs, const DateTime& rhs) {
    return std::tie(lhs.mYear, lhs.mMonth, lhs.mDay, lhs.mTime) <
           std:: tie(rhs.mYear, rhs.mMonth, rhs.mDay, rhs.mTime);
}

unsigned DateTime::dateToDays() noexcept{
    unsigned y = mYear;
    y -= mMonth <= 2;
    const unsigned era = (y >= 0 ? y : y-399) / 400;
    const unsigned yoe = (y - era * 400);      
    const unsigned doy = (153*(mMonth > 2 ? mMonth-3 : mMonth+9) + 2) / 5 + mDay-1; 
    const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;         
    return era * 146097 + (doe) - 719468;
}

DateTime DateTime::daysToDate(unsigned days) noexcept {
    days += 719468;
    const unsigned era = (days >= 0 ? days : days - 146096) / 146097;
    const unsigned doe = (days - era * 146097);          
    const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  
    const unsigned y = (yoe) + era * 400;
    const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                
    const unsigned mp = (5*doy + 2)/153;      
    const unsigned d = doy - (153*mp+2)/5 + 1;
    const unsigned m = mp < 10 ? mp+3 : mp-9;

    return DateTime(y + (m <= 2), m, d);
}

std::ostream& operator << (std::ostream &out, const DateTime& date) {
    out <<  std::setfill('0') << std::setw(2) << date.mDay << "."  <<
            std::setfill('0') << std::setw(2) << date.mMonth <<"." <<
            std::setfill('0') << std::setw(4) << date.mYear <<" " << date.mTime << ":00";
    return out;
}


unsigned DateTime::getTime() const { return mTime; }
void DateTime::setDay (unsigned day) { mDay = day; }
void DateTime::setTime(const unsigned time) { 
    mTime = time;
    if (time > 23) {
        *this = *this + (time/23);
        this->mTime = time % 23;
    }
}


unsigned DateTime::daysInMonth() const { 
    unsigned monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(mYear) ) monthDays[1] = 29;
    return monthDays[mMonth-1];
}


DateTime DateTime::currDateTime() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    DateTime today ( (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday, now->tm_hour);
    return today;
}

std::string DateTime::formatDate () {
    std::ostringstream out;
    out << mDay <<"." << mMonth <<"." << mYear << " "
    << std::setfill(' ') << std::setw(9) << dayOfWeek() << " |";
    return out.str();
}


std::string DateTime::dayOfWeek () const {
    unsigned y = mYear;
    const unsigned t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if ( mMonth < 3 ) y -= 1;
    unsigned i = (y + y/4 - y/100 + y/400 + t[mMonth-1] + mDay) % 7;
    const std::string weekDays [7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    return weekDays[i];
}

void DateTime::resetWeek () {
    unsigned y = mYear;
    const unsigned t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if ( mMonth < 3 ) y -= 1;
    unsigned i = (y + y/4 - y/100 + y/400 + t[mMonth-1] + mDay) % 7;
    const std::string weekDays [7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    
    const unsigned backToMonday [7] ={6, 0 , 1, 2, 3, 4, 5}; // days need to substracts to set the date to last to Monday (first day of week)
    unsigned days = dateToDays();
    days -= backToMonday[i];
    *this = daysToDate(days);
}

DateTime DateTime::operator ++ () {
    *this = daysToDate(dateToDays() + 1);
    return *this;
}

DateTime DateTime::operator + (unsigned days) {
    *this = daysToDate(dateToDays() + days);
    return *this;
}

bool DateTime::operator == (const DateTime& rhs) const {
    return std::tie(mYear, mMonth, mDay, mTime) ==
           std:: tie(rhs.mYear, rhs.mMonth, rhs.mDay, rhs.mTime);
}

bool DateTime::operator != (const DateTime& other) const {
    return !(*this == other);
}

// bool DateTime::operator < (const DateTime& rhs) const {
//     return std::tie(mYear, mMonth, mDay, mTime) <
//            std:: tie(rhs.mYear, rhs.mMonth, rhs.mDay, rhs.mTime);
// }
