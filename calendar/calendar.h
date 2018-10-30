#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

typedef struct Date{
    int year;
    int month;
    int day;
}Date;

typedef struct Time{
    int hour;
    int minute;
}Time;

typedef struct Event{
    Date date;
    Time start;
    Time ends;
    char* name;
    char* location;
    char* comment;
}Event;

Event createevent(Date date, Time start, Time ends, char const* name, char const* location, char const* comment);
#endif // CALENDAR_H_INCLUDED
