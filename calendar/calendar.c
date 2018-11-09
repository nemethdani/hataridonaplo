/**
* @file calendar.c
* @brief a naptár által láncolt listákkal,
* eseményekkel kapcsolatos függvények
*
* @author Németh Dániel
*/

#include "calendar.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

//#include "debugmalloc.h"

int starttime(Event* event){
    return mktime(&(event->start));


}
/**
* Ez a függvény létrehoz egy eseményt a megadott paraméterek alapján,
*és egy Event típus-ra mutató pointert ad vissza
*
*
*
*/
Event* createevent(Date date, Time start, Time ends, char* name, char* location, char* comment){
    Event *event=(Event*) malloc(sizeof(Event));
    if(event==NULL) return NULL;
    //event.date=date;
    event->start.tm_year=date.year;
    event->start.tm_mon=date.month;
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
/**
* Ez a függvény töröl egy eseményt a láncolt listából,
*és felszabadítja a memóriáját
*
* @param listelement A láncolt lista törölni kívánt eseményét
*tartalmazó listaelemre mutató pointer
*
*/
bool deleteEvent(EventListElement* listelement){
    if(listelement==NULL || listelement->event==NULL) return false;
    if(freeEvent(listelement)==false){
            printf("nem sikerult az esemenyt felszabaditani");
            return false;
    }
    listelement->prev->next=listelement->next;
    listelement->next->prev=listelement->prev;
    free(listelement);
    return true;
}
/**
* Esemény módosítása egy új létrehozásával
*és a régi törlésével
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
* @param listelement A láncolt lista törölni kívánt eseményét
*tartalmazó listaelemre mutató pointer
*
*/
bool modifyEvent(EventList* eventlist, EventListElement* listelement,Date date, Time start, Time ends, char* name, char* location, char* comment ){
    Event* newevent=createevent(date, start, ends, name, location, comment);
    if(newevent==NULL) return false;
    if(insertEventToListBackwards(eventlist,newevent)==false) return false;
    if(deleteEvent(listelement)==NULL) return false;
    return true;


}

void printevent(Event* event){
    printf("%d %d %d %d %d %d %d %s %s %s\n",
             event->start.tm_year,
             event->start.tm_mon,
             event->start.tm_mday,
             event->start.tm_hour,
             event->start.tm_min,
             event->ends.tm_hour,
             event->ends.tm_min,
             event->name,
             event->location,
             event->comment);
}

void printevent_short(Event* event){
    printf("%.2d.%.2d %.2d:%.2d %s %s\n",
             event->start.tm_mon,
             event->start.tm_mday,
             event->start.tm_hour,
             event->start.tm_min,
             event->name,
             event->location);
}
/**
*Duplán láncolt lista létrehozása az eseményeknek,
*két strázyával
*@return a listára mutató pointer
*
*
*/
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
/**
* A listába illeszt be egy eseményt hátulról
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
* @param listelement A láncolt lista törölni kívánt eseményét
*        tartalmazó listaelemre mutató pointer
* @return false, ha hiba történt, true, ha minden rendben
*/
bool insertEventToListBackwards(EventList* eventlist,Event* event){
    if(eventlist==NULL) return false;
    EventListElement* element=(EventListElement*) malloc(sizeof(EventListElement));
    if (element==NULL) return false;
    element->event=event;

    ///moving MOGE szurjuk be az uj elemet
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

bool freeEvent(EventListElement* listelement){
    if(listelement==NULL || listelement->event==NULL) return false;
    free(listelement->event->comment);
    free(listelement->event->location);
    free(listelement->event->name);
    free(listelement->event);
    return true;
}
/**
* Felszabadítja a láncolt listát és annak eseményeit
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
*
* @return false, ha hiba történt, true, ha minden rendben
*/
bool freeEventList(EventList* eventlist){
    EventListElement* list=eventlist->first;
    while(list){
        EventListElement* list_temp=list->next;
        freeEvent(list);
        free(list);
        list=list_temp;
    }
    free(eventlist);
    return true;
}
