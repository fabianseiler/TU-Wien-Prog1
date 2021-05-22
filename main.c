#include <stdio.h>
#include <ctype.h>
#include "string.h"

void my_getline(char input[], long len);
long get_letters(char text[]);
long get_others(char text[]);
char char_check();
void analyze_text(char text[]);
char* get_letters_ptr(char text[]);
char* get_others_ptr(char text[]);
void analyze_text_ptr(char text[]);
void trim_text(char text[]);

#define N 100


int main(){

    while (1){

        char input[N];
        char prog_end;

        printf("Texteingabe:");
        my_getline(input, N);

        if (get_letters(input) == 0) {
            printf("Andere Zeichen am Anfang: %ld\n", get_others(input));
        }
        else{
            printf("Buchstaben am Anfang: %ld\n", get_letters(input));
        }
        analyze_text(input);
        analyze_text_ptr(input);
        trim_text(input);

        prog_end = char_check();
        if (prog_end == 'n'){                  // check if programm should end
            printf("\n------PROGRAMM-ENDE-------");
            break;
        }

    }
    return 0;
}

void my_getline(char input[], long len){

   char c;
   for(int i=0; i<len-1; i++){
       c = getchar();
       if (c != '\n'){
           input[i] = c;
       }
       else{
           input[i]= '\0';
           break;
       }
   }
    fflush(stdin);
    input[len]= '\0';
}

long get_letters(char text[]){

    int len = 0;
    if (isalpha(text[0]) == 0){
        return 0;
    }
    else{
        len++;
        for (int i=1; i < strlen(text); i++ ){
            if (isalpha(text[i]) != 0){
                len++;
            }
            else{
                break;
            }
        }
    return len;
    }
}

long get_others(char text[]){

    int len = 0;
    if (isalpha(text[0]) && !isspace(text[0])){
        return 0;
    }
    else{
        len++;
        for (int i=1; i < strlen(text); i++ ){
            if (isalpha(text[i]) == 0){
                len++;
            }
            else{
                break;
            }
        }
        return len;
    }
}

char char_check(){
    // gets char as input, checks if it's valid and returns the char

    int end_char;
    printf("Nochmal 'y' oder 'n':");
    end_char = getchar();
    if (end_char == 'n'){
        return end_char;
    }
    do{
        while ((end_char = getchar()) != '\n' && end_char != EOF);
        printf("Bitte 'y' oder 'n' eingeben:");
        end_char = getchar();
    }while (end_char != 'y' && end_char != 'n' || getchar() != '\n');
    return end_char;

}

void analyze_text(char text[]) {

    int len = 0;
    int wrd_count = 0;
    int stats[10] = {0};
    char cpy_text[N] = {0};
    cpy_text[N-1] = '\0';
    strcpy(cpy_text, text);

    while (len <= strlen(text)) {                //loop unti len reaches the max value
        if (get_letters(cpy_text) > 0){
            wrd_count++;
            len += get_letters(cpy_text) + 1;
            get_letters(cpy_text) >= 10 ? stats[9]++ : stats[get_letters(cpy_text)-1]++;
        }
        else {
            len += get_others(cpy_text);
        }

        for (int i = 0;i <= strlen(text); i++) {  //for loops like a selective strncpy
            cpy_text[i] = text[i + len];
        }
        for (int i = strlen(text) + 1; i < N-1; i++) {     //filling the rest of cpy_text with 0
            cpy_text[i] = 0;
        }
        cpy_text[N-1] = '\0';
    }
    printf("Wortanzahl: %d\t\t\n", wrd_count);
    printf("Statistik:\n");
    printf("--------------------------------------\n");
    for (int i = 1; i <= 9; i++) {
        printf("Laenge: %d\t | \tHaeufigkeit: %d\n", i, stats[i - 1]);
    }
    printf("Laenge: >=10\t | \tHaeufigkeit: %d\n", stats[9]);
    printf("--------------------------------------\n");
}

char* get_letters_ptr(char text[]){

    long len = get_letters(text);
    if (get_letters(text) < strlen(text)){
        char *p = &text[len];
        return p;
    }
    else {
        return NULL;
    }
}

char* get_others_ptr(char text[]){

    long len = get_others(text);
    if (get_others(text) < strlen(text)){
        char *p = &text[len];
        return p;
    }
    else{
        return NULL;
    }
}

void analyze_text_ptr(char text[]) {

    int size;
    int len = 0;
    int wrd_count = 0;
    int stats[10] = {0};
    char cpy_text[N] = {0};
    cpy_text[N-1] = '\0';
    strcpy(cpy_text, text);

    while (get_others_ptr(cpy_text) != NULL) {                //loop unti len reaches the max value
        if (get_letters_ptr(cpy_text) != cpy_text){
            wrd_count++;
            if (get_letters_ptr(cpy_text) == NULL){
                size = (long)strlen(cpy_text);
            }
            else{
                size = (long)get_letters_ptr(cpy_text)-(long)cpy_text;
            }
            len += size;
            size >= 10 ? stats[9]++ : stats[size-1]++;
        }
        else {
            if (get_others_ptr(cpy_text) == NULL){
                size = (long)strlen(cpy_text);
            }
            else{
                size = (long)get_others_ptr(cpy_text)-(long)cpy_text;
            }
            len += size;
        }
        for (int i = 0;i <= strlen(cpy_text); i++) {        //for loops like a selective strncpy
            cpy_text[i] = text[i + len];
        }
        for (int i = strlen(text) + 1; i < N-1; i++) {        //filling the rest of cpy_text with 0
            cpy_text[i] = 0;
        }
        cpy_text[N-1] = '\0';
    }
    printf("Wortanzahl: %d\t\t\n", wrd_count);
    printf("Statistik:\n");
    printf("--------------------------------------\n");
    for (int i = 1; i <= 9; i++) {
        printf("Laenge: %d\t | \tHaeufigkeit: %d\n", i, stats[i - 1]);
    }
    printf("Laenge: >=10\t | \tHaeufigkeit: %d\n", stats[9]);
    printf("--------------------------------------\n");
}

void trim_text(char text[]){


}
