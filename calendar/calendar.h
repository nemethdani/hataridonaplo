#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED
#include <stdbool.h>
#include <time.h>

typedef struct tm Tm;

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
    Tm start;
    Tm ends;
    char* name;
    char* location;
    char* comment;
}Event;

typedef struct EventListElement{
    Event *event;
    struct EventListElement *prev, *next;
}EventListElement;

typedef struct EventList{
    EventListElement *first;
    EventListElement *last;
}EventList;

int starttime(Event* event);
Event* createevent(Date date, Time start, Time ends, char* name, char* location, char* comment);
bool deleteEvent(EventList* eventlist, EventListElement* listelement);
bool modifyEvent(EventList* eventlist, EventListElement* listelement,Date date, Time start, Time ends, char* name, char* location, char* comment );
EventList* initEventList(void);
bool insertEventToListBackwards(EventList* eventlist,Event* event);
bool printEventList(EventList* eventlist);
bool freeEvent(EventList* eventlist, EventListElement* listelement);
bool freeEventList(EventList* eventlist);
#endif // CALENDAR_H_INCLUDED
