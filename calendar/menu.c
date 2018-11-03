#include <stdio.h>
#include <ctype.h>
#include "calendar.h"

void mainmenu(EventList* eventlist){
    //enum mmenu{let,ker,men,ki};
    printf("\nMit szeretnel tenni?\n\n");
    printf("(1) Esemeny (l)etrehozasa\n");
    printf("(2) Esemenyek (k)eresese\n");
    printf("(3) Modositasok (m)entese\n");
    printf("(4) (B)ezaras\n");

    char input;
    scanf(" %c",&input);
    input=tolower(input);
    switch(input){
        case '1':
        case 'l':
            create_console();
            break;
        case '2':
        case 'k':
            search_menu();
            break;
        case '3':
        case 'm':
            saving_console(eventlist);
            break;
        case '4':
        case 'b':
            exit_console();
            break;
        default:
            printf("irj be mast!\n");
            break;
    }
}

void create_console(){

}
void search_menu(){

}
void exit_console(){
    printf("tenyleg ki szeretnel elpni?\n");
}
void saving_console(EventList* eventlist){
    printf("tenyleg el szeretned menteni?\n");
    printf("(1) (M)entes\n");
    printf("(2) (V)issza\n");
    char input;
    scanf(" %c",&input);
    input=tolower(input);
    switch (input){
        case '1':
        case 'm':
            calendarsave(eventlist);
            printf("mentettem\n");
            //scanf("%c",&input);
            mainmenu(eventlist);
            break;
        default:
            //printf("uss be mast\n");
            mainmenu(eventlist);
            break;

    }
}
