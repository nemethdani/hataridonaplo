/*! \mainpage Határidőnapló
 *
 * \section intro_sec Introduction
 *
 * BME prog1 házi
 *
 * \section Ami már működik (UI)
 * Naptár betöltése fájlból, kiírása fájlba
 *
 * Esemény keresése név szerint
 *
 * Program bezárása
 *
 * háttérben: eseméynek beszűrása, törlése, módosítása, kiírása
 *
 *
 * \section Ami nem működik
 * Események keresése idő szerint
 *
 * Események módosítása
 */

/**
* @file main.c
* @brief ez a főfájl tölti be az adatokat a fájlból
* és nyitja meg a főmenüt.
*
* @author Németh Dániel
*/

#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "file.h"

//#include "debugmalloc.h"

/**
 *ez a főfüggvény tölti be az adatokat a fájlból
* és nyitja meg a főmenüt.
 */
int main()
{
    Date date={date.year=2018,date.month=10,date.day=26};
    Time start={start.hour=19,start.minute=51};
    Time end={end.hour=22,end.minute=11};
    Event *event=createevent(date,start,end,"esemeny neve","esemeny helye","megjegyzes");

    Date date2={date.year=2017,date.month=9,date.day=25};
    Time start2={start.hour=17,start.minute=50};
    Time end2={end.hour=21,end.minute=10};
    Event *event2=createevent(date2,start2,end2,"esemeny neve2","esemeny helye2","megjegyzes2");
    //printevent(event);
    EventList* eventlist=initEventList();
    if(calendarload(eventlist)==false) printf("nem sikerult beolvasni");
    //if(insertEventToListBackwards(eventlist,event)==false) printf("nem illesztette be");
    //if(insertEventToListBackwards(eventlist,event2)==false) printf("nem illesztette be");
    //printevent(eventlist->first->next->event);
    //printevent(eventlist->first->next->next->event);
    //printevent(eventlist->last->prev->event);
    //if(deleteEvent(eventlist,eventlist->first->next)==false) printf("nem sikerult torolni");
    //modifyEvent(eventlist,eventlist->first->next,date2,start2,end2,"modositott nev","modositott hely","modositott comment");
    //printEventList(eventlist);

    //printf("%d\n",strlen(eventlist->last->prev->event->location));
    //if(calendarsave(eventlist)==false) printf("nem sikerult menteni");
    //printf("%d",(eventlist->first->next->event==NULL));

    mainmenu(eventlist);
    //if(freeEventList(eventlist)==false) printf("nem sikerult felszabaditani a listat");
    return 0;
}
