#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <stdbool.h>
#include "calendar.h"

bool calendarsave(EventList* eventlist);
bool calenderload(EventList* eventlist);

#endif // FILE_H_INCLUDED
