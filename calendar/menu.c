#include <stdio.h>
#include <ctype.h>
#include "calendar.h"
#include <stdlib.h>
#include <string.h>

/**
* @file file.c
* @brief A menuk kezelésére szolgáló függvények
*/

/**
* Beolvassa a felhasználó által megadott parancs karakterét
*
*/
char scaninput(){
    char input;
    scanf(" %c",&input);
    input=tolower(input);
    return input;
}


/**
* Kiírja a főmenüt, meghívja a megadott parancshoz tartozó függvényt
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
*/
void mainmenu(EventList* eventlist){
    //enum mmenu{let,ker,men,ki};
    printf("\nMit szeretnel tenni?\n\n");
    printf("(1) Esemeny (l)etrehozasa\n");
    printf("(2) Esemenyek (k)eresese\n");
    printf("(3) Modositasok (m)entese\n");
    printf("(4) (B)ezaras\n");


    switch(scaninput()){
        case '1':
        case 'l':
            create_console();
            break;
        case '2':
        case 'k':
            search_menu(eventlist);
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

/**
* Itt lehet kiválasztani, hogy hogyan szeretnénk keresni
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
*/
void search_menu(EventList* eventlist){
       printf("\nHogyan szeretnel keresni?\n");
       printf("(1) (E)semeny neve szerint\n");
       printf("(2) (N)ap szerint\n");
       printf("(3) (H)et szerint\n");
       printf("(4) H(o)nap szerint\n\n");
       printf("(5) (V)issza a fomenube\n");
    switch(scaninput()){
    case '1':
    case 'e':
        searchbyname(eventlist);
        break;
    case '2':
    case 'n':
        //searchbyday();
        break;
    case '3':
    case 'h':
        //searchbyweek();
        break;
    case '4':
    case 'o':
        //searchbymonth();
        break;
    case '5':
    case 'v':
        mainmenu(eventlist);
        break;
    }
}



/**
* Megkérdezi, hogy tényleg szertnénk e menteni
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
*/
void saving_console(EventList* eventlist){
    printf("\ntenyleg el szeretned menteni?\n");
    printf("(1) (M)entes\n");
    printf("(2) (V)issza\n");

    switch (scaninput()){
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
/**
* Kilépés a programból
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
*/
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
/**
* Itt tudjuk módosítani és törölni a kiválasztott eseményt
* @param editevent A törölni kívánt eseményre mutató pointer
*/
void eventeditor(Event* editevent){
    printf("this is the event editor\n");
}

/**
* A keresés által visszaadott események listájából az esemény kiválasztása módosítás céljából
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
* @param findlist a keresés által előállított találati lista
*/
void scan_searchmenu_command(int i, EventList* eventlist, EventList* findlist){
    char command=scaninput();
    if(command=='f' || command==(i+'0')) mainmenu(eventlist);
    else if(command=='k' || command==(i-1+'0')) search_menu(eventlist);
    else if(isalpha(command)){
        printf("irj be mast\n");
        scan_searchmenu_command(i,eventlist,findlist);
    }
    else{
        int comm=command - '0';
        if(comm>i) {
            printf("irj be mast\n");
            scan_searchmenu_command(i,eventlist,findlist);
        }
        else{
            EventListElement* editelement=findlist->first->next;
            int iter=1;
            while(iter!=comm){
                editelement=editelement->next;
                iter++;
            }
            Event* editevent=editelement->event;
            eventeditor(editevent);
        }
    }
}
/**
* Esemény keresése annak neve szerint
* Az esemény nevéből legalább 3 összefüggő karakter kell
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
*/
void searchbyname(EventList* eventlist){
    printf("\nIrj be legalabb 3 osszefuggo karaktert az esemeny nevebol!\n");
    char search[128]={0};
    while(strlen(&search)<3){
            printf("legalabb 3 karaktert irjal\n");
            scanf("%s",search);
    }
    EventListElement* moving=eventlist->first->next;
    int i=1;
    Event* e;
    EventList* findlist=initEventList();
    while(moving!=eventlist->last){

        if(strstr(moving->event->name,&search)!=NULL){
            e=moving->event;
            printf("(%d) ",i);
            printevent_short(e);
            printf("\n");
            //put event to new linkedlist
            if(insertEventToListBackwards(findlist,e)==false) printf("nem illesztette be a talalati listaba\n");
            ++i;

        }
        moving=moving->next;

    }
    //print extra menu
    printf("(%d) (K)ereses menu\n",i);
    i++;
    printf("(%d) (F)omenu\n",i);
    scan_searchmenu_command(i,eventlist,findlist);
    return;
}
