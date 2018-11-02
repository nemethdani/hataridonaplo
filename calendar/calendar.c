#include "calendar.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int starttime(Event* event){
    return mktime(&(event->start));


}

Event* createevent(Date date, Time start, Time ends, char* name, char* location, char* comment){
    Event *event=(Event*) malloc(sizeof(Event));
    if(event==NULL) return NULL;
    //event.date=date;
    event->start.tm_year=date.year-1900;
    event->start.tm_mon=date.month-1;
    event->start.tm_mday=date.day;
    event->start.tm_hour=start.hour;
    event->start.tm_min=start.minute;
    event->ends=event->start;
    event->ends.tm_hour=ends.hour;
    event->ends.tm_min=ends.minute;
    char* newname=(char*) malloc((strlen(name)+1)*sizeof(char));
    if(newname ==NULL) newname=NULL;
    strcpy(newname,name);
    event->name=newname;
    char* newloc=(char*) malloc((strlen(location)+1)*sizeof(char));
    if(newloc==NULL) newloc=NULL;
    strcpy(newloc,location);
    event->location=newloc;
    char* newcomment=(char*) malloc((strlen(comment)+1)*sizeof(char));
    if (newcomment==NULL) newcomment=NULL;
    strcpy(newcomment,comment);
    event->comment=newcomment;
    return event;
}

void printevent(Event* event){
    printf("%d %d %d %d %d %d %d %s %s %s\n",
             event->start.tm_year+1900,
             event->start.tm_mon+1,
             event->start.tm_mday,
             event->start.tm_hour,
             event->start.tm_min,
             event->ends.tm_hour,
             event->ends.tm_min,
             event->name,
             event->location,
             event->comment);
}

EventList* initEventList(void){
    EventList* eventlist=(EventList*) malloc(sizeof(EventList));
    EventListElement* sentinel1=(EventListElement*) malloc(sizeof(EventListElement));
    EventListElement* sentinel2=(EventListElement*) malloc(sizeof(EventListElement));
    eventlist->first=sentinel1;
    eventlist->last=sentinel2;
    eventlist->first->next=eventlist->last;
    eventlist->last->prev=eventlist->first;
    return eventlist;
    }

bool insertEventToListBackwards(EventList* eventlist,Event* event){
    if(eventlist==NULL) return false;
    EventListElement* element=(EventListElement*) malloc(sizeof(EventListElement));
    if (element==NULL) return false;
    element->event=event;

    //moving MOGE szurunk be
    EventListElement* moving;
    moving=eventlist->last->prev;
    while(moving!=eventlist->first &&  (starttime(moving->event) > starttime(event))){
        moving=moving->prev;
    }
    element->prev=moving;
    element->next=moving->next;

    moving->next->prev=element;
    moving->next=element;

    return true;
}

bool printEventList(EventList* eventlist){


    EventListElement* moving;
    moving=eventlist->first->next;
    while(moving!=eventlist->last){
        printevent(moving->event);
        moving=moving->next;
    }
    return true;
}
