#include <stdio.h>
#include <ctype.h>
#include "calendar.h"
#include <stdlib.h>

char scaninput(){
    char input;
    scanf(" %c",&input);
    input=tolower(input);
    return input;
}

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
            exit_console(eventlist);
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

void saving_console(EventList* eventlist){
    printf("\ntenyleg el szeretned menteni?\n");
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

void exit_console(EventList* eventlist){
    printf("\n(1) Kilepes (m)entessel\n");
    printf("(2) (K)ilepes mentes nelkul\n");
    printf("(3) (V)issza\n");

    switch(scaninput()){

            case '1':
            case 'm':
                calendarsave(eventlist);
                printf("mentettem\n");
                if(freeEventList(eventlist)==false) printf("nem sikerult felszabaditani a listat");
                else exit(0);
                break;
            case '2':
            case 'k':
                if(freeEventList(eventlist)==false) printf("nem sikerult felszabaditani a listat");
                else exit(0);
                break;
            default:
                mainmenu(eventlist);
                break;

    }
}
