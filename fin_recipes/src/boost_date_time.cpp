#include "boost_date_time.hpp"

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include <iostream>
using namespace boost::gregorian;
using namespace boost::posix_time;

void ex_date_time(){
    boost::gregorian::date d(2014, 4, 1); // creating a date
    std::cout << " date: " << d << "\n";
    boost::posix_time::ptime dt;
    std::stringstream ss("2014-mar-01 10:01:01.01");
    ss >> dt;
    std::cout << " date time just created: " << dt << "\n";
    ptime now = second_clock::local_time(); // get the current time from the clock
    date today = now.date();                // Get the date part out of the time
    std::cout << " today: " << today << "\n";
    date tomorrow = today + days(1); // add one date
    ptime tomorrow_start(tomorrow); // midnight
    time_duration remaining = tomorrow_start - now;
    std::cout << "Time left till midnight: " << to_simple_string(remaining) << "\n";
}
