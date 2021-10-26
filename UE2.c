#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <duma.h>

typedef struct Element_s {
    char songtitle[256], interpreter[256];
    struct Element_s *next, *prev;
} Element_t;

void read_from_keyboard(Element_t *item);
void readString(char *name, char *text, long len);  // Extra Func
long readValue(void);                               // Extra Func
Element_t *allocate_element();


int main()
{
    long c;
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

        default:
            printf("Error bei Eingabe!\n");
            break;
        }
    }
}

void read_from_keyboard(Element_t *item){

    if(item != NULL){
        if(item->interpreter != NULL && item->songtitle != NULL){
        readString("Interpreter", item->interpreter, 256);
        readString("Song Title", item->songtitle, 256);
        }
    }
}

void readString(char *name, char *text, long len){
    // reads in a string with a max length of len and clears stdin
    printf("%s:", name);

    char c, control_char;
    for (long i = 0; i < len - 1; i++){     // reads in a char until '\n' was entered or len was reached
        c = getchar();
        if (c != '\n') {
            text[i] = c;
        }
        else {
            text[i] = '\0';
            break;
        }
    }
    if (strlen(text) >= len-1) {            // clears stdin if more char than len where entered
        text[len-1] = '\0';
        while ((control_char = getchar()) != '\n' && control_char != EOF){}
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

Element_t *allocate_element(){

    Element_t *entry = malloc(sizeof(Element_t));
    entry->interpreter = malloc(256*sizeof(char));
    entry->songtitle = malloc(256*sizeof(char));
}


