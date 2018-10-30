#include "calendar.h"
#include <string.h>
#include <stdio.h>

Event createevent(Date date, Time start, Time ends, char* name, char* location, char* comment){
    Event event;
    event.date=date;
    event.start=start;
    event.ends=ends;
    char* newname=(char*) malloc((strlen(name)+1)*sizeof(char));
    if(newname ==NULL) newname=NULL;
    strcpy(newname,name);
    event.name=newname;
    char* newloc=(char*) malloc((strlen(location)+1)*sizeof(char));
    if(newloc==NULL) newloc=NULL;
    strcpy(newloc,location);
    event.location=newloc;
    char* newcomment=(char*) malloc((strlen(comment)+1)*sizeof(char));
    if (newcomment==NULL) newcomment=NULL;
    strcpy(newcomment,comment);
    event.comment=newcomment;
    return event;
}

void printevent(Event event){
    printf("%d %d %d %d %d %d %d %s %s %s\n",
             event.date.year,
             event.date.month,
             event.date.day,
             event.start.hour,
             event.start.minute,
             event.ends.hour,
             event.ends.minute,
             event.name,
             event.location,
             event.comment);
}
