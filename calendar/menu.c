#include <stdio.h>
#include <ctype.h>
#include "calendar.h"

void mainmenu(EventList* eventlist){
    //enum mmenu{let,ker,men,ki};
    printf("(1) Esemeny (l)etrehozasa\n");
    printf("(2) Esemenyek (k)eresese\n");
    printf("(3) Modositasok (m)entese\n");
    printf("(4) (K)ilepes\n");

    char input;
    scanf(" %c",input);
    input=tolower(input);
    switch(input){
        case 1:
        case 'l':
            create_console();
            break;
        case 2:
        case 'k':
            search_menu();
            break;
        case 3:
        case 'm':
            calendarsave(eventlist);
            break;
        case 4:
        case 'k':
            exit_console();
            break;
        default:
            printf("irj be mast!");
            break;
    }
}
