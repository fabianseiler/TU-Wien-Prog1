#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <duma.h>

typedef struct Element_s {
    char songtitle[256], interpreter[256];
    struct Element_s *next, *prev;
} Element_t;


long readValue(void);                               // Extra Func
void read_from_keyboard(Element_t *item);
Element_t *allocate_element();
Element_t *insert_last(Element_t *list);
void free_list(Element_t **list);



int main()
{
    long c;
    Element_t *Playlist;
    while(1){
        printf("0: Programm beenden\n");
        printf("1: Neuen Eintrag einlesen und am Ende einfuegen\n");
        printf("2: Liste ausgeben\n");
        printf("3: Liste loeschen\n");
        printf("4: Anzahl der Elemente ausgeben\n");
        printf("5: Element an der Stelle x ausgeben\n");
        printf("6: Neuen Eintrag einlesen und an der Stelle x einfuegen\n");
        printf("7: Eintrag an der Stelle x loeschen\n");
        printf("8: Liste in umgekehrter Reihenfolge ausgeben\n");
        printf("9: Liste in zufaelliger Reihenfolge ausgeben\n");
        printf("10: Liste aufsteigend nach songtitle sortieren\n");
        printf("11: Liste absteigend nach songtitle sortieren\n");
        printf("12: Duplikate aus Liste entfernen\n");
        printf("13: Liste um x rotieren\n");

        c = readValue();

        switch(c){
        case 0:
            printf("Programm beendet!\n");
            return 0;
        case 1:
            insert_last(Playlist);
            break;
        default:
            printf("Error bei Eingabe!\n");
            break;
        }
    }
}

long readValue(void){
    // reads in a long value and clears stdin
    long value;
    char term;
    char control_char;
    printf("\nBitte eine Zahl eingeben:");
    while(1) {
        if (scanf("%ld%c", &value, &term) != 2 || term != '\n'){                // check if long and '\n' was entered
            fprintf(stderr, "Bitte eine Zahl eingeben:");
            while ((control_char = getchar()) != '\n' && control_char != EOF){} // clears stdin
        }
        else break;
    }
    return value;
}


void read_from_keyboard(Element_t *item){

    if(item != NULL){
        if(item->interpreter != NULL && item->songtitle != NULL){
            printf("Iterpreter:");
            fgets(item->interpreter, 256, stdin);
            printf("Songtitle:");
            fgets(item->songtitle, 256, stdin);



        }
        else printf("Error bei Eingabe!\n");
    }
    else printf("Error bei Eingabe!\n");
}


Element_t *allocate_element(){

    Element_t *entry = malloc(sizeof(Element_t));
    if(entry == NULL){
        printf("Error bei allozierung!\n");
    }
    else{
    read_from_keyboard(entry);
    entry->next = NULL;
    entry->prev = NULL;
    }
}

Element_t *insert_last(Element_t *list){
// Checks if the list is exists, and adds an element to the next pointer if it is
    if(list == NULL){
        allocate_element(list);
    }
    else{
        Element_t *next_ele;
        allocate_element(next_ele);
        list->next = next_ele;
    }
    return list;
}

void free_list(Element_t **list){

    Element_t *temp=list->next;
    while(temp != NULL){

        temp = temp->next;
    }
    while(temp->prev != NULL){
        free(temp);
        temp = temp->prev;
    }
    free(temp);
    free(list);
    list = NULL;
}
