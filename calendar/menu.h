#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void mainmenu(EventList* eventlist);
void create_console(EventList* eventlist)
void search_menu();
void exit_console();
void saving_console(EventList* eventlist);
char scaninput();
void eventeditor(Event* editevent, EventList* eventlist, EventListElement* listelement, Bytime bytime,Tm* timeinfo,int sweek)

#endif // MENU_H_INCLUDED
