#include <stdio.h>
#include <ctype.h>
#include "calendar.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//#include "debugmalloc.h"

/**
* @file file.c
* @brief A menuk kezelésére szolgáló függvények
*/


typedef enum {month,week,day,no,name}Bytime;


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
            create_console(eventlist);
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


char *hosszu_sort_olvas() {
    int db = 0;
    char *sor = (char*) malloc(sizeof(char) * 1);
    sor[0] = '\0';
    char ujkar;
    while (scanf("%c", &ujkar) == 1 && ujkar != '\n') {
        /* itt a tömb nyújtása */
        char *ujtomb = (char*) malloc(sizeof(char) * (db+1+1));
        for (int i = 0; i < db; ++i)
            ujtomb[i] = sor[i];
        free(sor);
        sor = ujtomb;
        ujtomb[db] = ujkar;
        ujtomb[db+1] = '\0';
        ++db;
    }

    return sor;
}

void scandate(Date* date){
    printf("Mi az esemeny datuma? (eeee.hh.dd)\n");
    scanf("%d.%d.%d",&date->year,&date->month,&date->day);
//    if(scanf("%d.%d.%d",&date->year,&date->month,&date->day)!=3 ||
//       date->month>12 ||
//       date->month<1 ||
//       date->day>31 ||
//       date->day<1){
//           printf("probald ujra\n");
//           scandate(date);
//       }

    return;
}
void scantime(Time* time){
    scanf("%d:%d",&time->hour,&time->minute);
//    if(scanf("%d:%d",time->hour,time->minute)!=2){
//        printf("probald ujra\n");
//        scantime(time);
//
//    }
    return;
}
/**
* Bekéri az esemény adatait és létrehozza az eseményt
*/
void create_console(EventList* eventlist){
    //Date date, Time start, Time ends, char* name, char* location, char* comment
    Date date;
    Time start, ends;


    scandate(&date);

    printf("Kerem az esemeny kezdo idejet! (oo:pp)\n");
    scantime(&start);
    printf("Kerem az esemeny befejezo idejet! (oo:pp)\n");
    scantime(&ends);
    getchar();

    printf("Kerem a nevet\n");
    char* name=hosszu_sort_olvas();
    //getchar();
    printf("Kerem a helyszint\n");
    char* loc=hosszu_sort_olvas();
    //getchar();
    printf("Kerem a megjegyzést\n");
    char* comm=hosszu_sort_olvas();
    //getchar();
    printf("%s %s %s",name,loc,comm);
    Event* e=createevent(date,start,ends,name,loc,comm);

    //printf("e: %d", e!=NULL);
    //printf("eventlist: %d", eventlist!=NULL);

    if(insertEventToListBackwards(eventlist,e)==false) printf("nem sikerult az esemenyt beilleszteni\n");
    eventeditor(e,eventlist,searchelement(e,eventlist),no,NULL,0,NULL);

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
        searchbytime(day,eventlist);
        break;
    case '3':
    case 'h':
        searchbytime(week,eventlist);
        break;
    case '4':
    case 'o':
        searchbytime(month,eventlist);
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
void eventeditor(Event* editevent, EventList* eventlist, EventListElement* listelement, Bytime bytime,Tm* timeinfo,int sweek,char* search){
    printevent(editevent);
    printf("\n(7) (M)odositasok fajlba mentese\n");
    printf("(8) (E)semeny torlese\n");
    if(bytime!=no) printf("(9) (V)issza a talalati listahoz\n");
    printf("(A) (U)j esemeny\n");
    printf("(B) Vissza a (f)omenube\n");

    switch(scaninput()){
    case '7':
    case 'm':
        calendarsave(eventlist);
        printf("mentettem\n");
        eventeditor(editevent, eventlist, listelement, bytime,timeinfo,sweek,search);
        break;
    case '8':
    case 'e':
        deleteEvent(listelement);
        break;
    case '9':
    case 'v':
        //searchbymonth(Tm* timeinfo,EventList* eventlist)
        //searchbytime(bytime, EventList* eventlist)
        switch(bytime){
        case month:
                searchbymonth(timeinfo,eventlist);
                break;
        case week:
                searchbyweek(sweek,timeinfo,eventlist);
                break;
        case day:
                searchbyday(timeinfo,eventlist);
                break;
        case name:
                searchbyname_iter(eventlist,search);
                break;
        deafult: break;
        }
    case 'a':
    case 'u':
        create_console(eventlist);
        break;
    case 'b':
    case 'f':
        mainmenu(eventlist);
        break;
    }

}

/**
* A keresés által visszaadott események listájából az esemény kiválasztása módosítás céljából
* @param eventlist A lista elejét és végét tartalmazó struktúrára mutató pointer
* @param findlist a keresés által előállított találati lista
*/
void scan_searchmenu_command(int i, EventList* eventlist, EventList* findlist, Bytime bytime, Tm* timeinfo, int sweek, char* search){
    char command=scaninput();
    if(command=='f' || command==(i+'0')) mainmenu(eventlist);
    else if(command=='k' || command==(i-1+'0')) search_menu(eventlist);
    else if(isalpha(command)){
        printf("irj be mast\n");
        scan_searchmenu_command(i,eventlist,findlist,bytime,timeinfo,sweek,search);
    }
    else{
        int comm=command - '0';
        if(comm>i) {
            printf("irj be mast\n");
            scan_searchmenu_command(i,eventlist,findlist,bytime,timeinfo,sweek,search);
        }
        else{
            EventListElement* editelement=findlist->first->next;
            int iter=1;
            while(iter!=comm){
                editelement=editelement->next;
                iter++;
            }
            Event* editevent=editelement->event;
            eventeditor(editevent,eventlist,editelement,bytime,timeinfo,sweek,search);
        }
    }
}

void searchbyname_iter(EventList* eventlist,char* search){
    EventListElement* moving=eventlist->first->next;
    int i=1;
    Event* e;
    EventList* findlist=initEventList();
    while(moving!=eventlist->last){

        if(strstr(moving->event->name,search)!=NULL){
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
    scan_searchmenu_command(i,eventlist,findlist,name,NULL,0,search);
    return;
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
    searchbyname_iter(eventlist,&search);

}
/***
* Megkeresi az eseményt hónap, hét vagy nap alapján
* Bekéri a felhasználótól a keresett időt
* Mindig az aktuális évben keres, ha hónapra vagy hétre keresünk
* Mindig az aktuális hónapban keres, ha napra keresünk
* Ha hétre k
* @param time lehetséges ésrtékek: month, week, day; ezek állítják be, hogy mi szerint keres a függvény
*/
void searchbytime(Bytime bytime, EventList* eventlist){
    int sweek;
    time_t rawtime;
    Tm * timeinfo;

    time(&rawtime);
    timeinfo=localtime(&rawtime);


    switch(bytime){
    case month:
            printf("Hanyadik ho?\n");
            scanf("%d",&timeinfo->tm_mon);
            searchbymonth(timeinfo,eventlist);
            break;
    case week:

            printf("Hanyadik het?\n");
            scanf("%d",&sweek);
            searchbyweek(sweek,timeinfo,eventlist);
            break;
    case day:
            printf("Hanyadik ho?\n");
            scanf("%d",&timeinfo->tm_mon);
            printf("Hanyadik nap?\n");
            scanf("%d",&timeinfo->tm_mday);
            searchbyday(timeinfo,eventlist);
            break;
    }
}
searchbymonth(Tm* timeinfo,EventList* eventlist){
    EventListElement* moving=eventlist->first->next;
    int i=1;
    Event* e;
    EventList* findlist=initEventList();
    while(moving!=eventlist->last){

        if(moving->event->start.tm_mon==timeinfo->tm_mon){
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
    scan_searchmenu_command(i,eventlist,findlist,month,timeinfo,0,NULL);
}

searchbyweek(int sweek, Tm timeinfo, EventList* eventlist){
    EventListElement* moving=eventlist->first->next;
    int i=1;
    Event* e;
    EventList* findlist=initEventList();
    while(moving!=eventlist->last){

        if(date2week(moving->event->start)==sweek){
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
    scan_searchmenu_command(i,eventlist,findlist,week,NULL,sweek,NULL);


}
searchbyday(Tm* timeinfo,EventList* eventlist){
    EventListElement* moving=eventlist->first->next;
    int i=1;
    Event* e;
    EventList* findlist=initEventList();
    while(moving!=eventlist->last){

        if(moving->event->start.tm_mon==timeinfo->tm_mon &&
           moving->event->start.tm_mday==timeinfo->tm_mday){
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
    scan_searchmenu_command(i,eventlist,findlist,day,timeinfo,0,NULL);
}

/**
*Kiszámítja a megadott dátum az év hányadik hetében van
*Az év első hete az, amelyik tartalmazza jan. 4-ét
*A hét hétfővel kezdődik
*ISO 8601
*@return 1-53
*/
int date2week(Tm* date){

    char buffer [2];


    strftime (buffer,80,"%V",date);
    return (buffer[0]-'0')*10 + (buffer[1]-'0');

}

