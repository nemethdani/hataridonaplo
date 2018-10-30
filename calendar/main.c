#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

int main()
{
    Date date={date.year=2018,date.month=10,date.day=26};
    Time start={start.hour=19,start.minute=51};
    Time end={end.hour=22,end.minute=11};
    Event event=createevent(date,start,end,"esemeny neve","esemeny helye","megjegyzes");
    printevent(event);
    //printf("%d",start.hour);
    return 0;
}
