#include <stdio.h>
#include "file.h"
#include "calendar.h"
#include <time.h>


bool calendarsave(EventList* eventlist){
    FILE *fp; /* fájl mutató (file pointer/handle) */

    fp = fopen("naptar.txt", "wt"); /* megnyitás */
    if (fp == NULL) {
       perror("Fájl megnyitása sikertelen");
       return false;    /* nem folytathatjuk! */
    }
    EventListElement* moving=eventlist->first->next;
    if(moving==NULL || moving==eventlist->last) return false;
    Event* me;
    while(moving!=eventlist->last){
        me=moving->event;
        fprintf(fp,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\n",
                me->start.tm_year,
                me->start.tm_mon,
                me->start.tm_mday,
                me->start.tm_hour,
                me->start.tm_min,
                me->ends.tm_hour,
                me->ends.tm_min,
                me->name,
                me->location,
                me->comment);

        moving=moving->next;
    }

    fclose(fp);
    return true;
}
