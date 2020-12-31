/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Zamansky
Assignment: Lab 10

*/

#include <iostream> 
#include <cmath>

class Time { 
public:
    int h;
    int m;
};

int minutesSinceMidnight(Time time) {
    // minutes since midnight
    return time.h * 60 + time.m;
}

int minutesUntil(Time earlier, Time later) {
    // minutes since midnight later - minutes since midnight earlier 
    return minutesSinceMidnight(later) - minutesSinceMidnight(earlier); 
}

Time addMinutes(Time time0, int min) {
    // set up time
    // add hours
    // add minutes
    int hours = (int) min / 60;
    int minutes  = time0.m + min % 60;
    hours += (int) minutes / 60;
    minutes = minutes % 60;
    Time t = {time0.h + hours, minutes};
    return t;
}

void printTime(Time t) {
    std::cout << t.h << ":" << t.m;
}

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

class Movie { 
public: 
    std::string title;
    Genre genre;     // only one genre per movie
    int duration;    // in minutes
};

class TimeSlot { 
public: 
    Movie movie;     // what movie
    Time startTime;  // when it starts
};

void printMovie(Movie mv){
    std::string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    std::cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

void printTimeSlot(TimeSlot ts) {
    // print movie title + duration
    printMovie(ts.movie);
    // print start time
    std::cout << " [starts at "; 
    printTime(ts.startTime);
    // print end time
    std::cout << ", ends by ";
    Time end = addMinutes(ts.startTime, ts.movie.duration);
    printTime(end);
    std::cout << "]" << std::endl;
}

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie) {
    Time end = addMinutes(ts.startTime, ts.movie.duration);
    TimeSlot ns = {nextMovie, end};
    return ns;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2) {
    // set up times
    Time ts1s = ts1.startTime;
    Time ts1e = addMinutes(ts1.startTime, ts1.movie.duration);
    Time ts2s = ts2.startTime;
    Time ts2e = addMinutes(ts2.startTime, ts2.movie.duration);
    
    // get int values
    int ts1sm = minutesSinceMidnight(ts1s);
    int ts1em = minutesSinceMidnight(ts1e);
    int ts2sm = minutesSinceMidnight(ts2s);
    int ts2em = minutesSinceMidnight(ts2e);
    
    if (ts1sm >= ts2sm && ts1sm <= ts2em) {
        return true;
    }
    else if (ts1em >= ts2sm && ts1em <= ts2em) {
        return true;
    }
    if (ts2sm >= ts1sm && ts2sm <= ts1em) {
        return true;
    }
    if (ts2em >= ts1sm && ts2em <= ts1em) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    // set up movies

    Movie movie1 = {"Back to the Future", COMEDY, 116};
    Movie movie2 = {"Black Panther", ACTION, 134};
    Movie movie3 = {"Burn the Stage: The Movie", ACTION, 85};
    Movie movie4 = {"Sorry to Bother You", COMEDY, 112};
    Movie movie5 = {"Get Out", ACTION, 104};

    // create timeslots
    TimeSlot morning = {movie1, {9, 15}};  
    TimeSlot daytime = {movie2, {12, 15}}; 
    TimeSlot evening = {movie2, {16, 45}}; 
    TimeSlot evening2 = {movie3, {19, 45}}; 
    TimeSlot evening3 = {movie4, {21, 30}}; 
    TimeSlot evening4 = scheduleAfter(evening, movie5);

    // cout
    
    printTimeSlot(morning);
    printTimeSlot(daytime);
    printTimeSlot(evening);
    printTimeSlot(evening4);
    printTimeSlot(evening3);
    printTimeSlot(evening2);

    return 0;
}
