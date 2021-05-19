#include <stdio.h>
#include <ctype.h>
#include "string.h"

void my_getline(char input[], long len);
long get_letters(char text[]);
long get_others(char text[]);
char char_check();
void analyze_text(char text[]);

#define N 100

//test
int main() {

    while (1) {


        char input[N];
        long len;
        long num_or_al;
        char prog_end;

        printf("Texteingabe:");
        my_getline(input, N);
        printf("Input: %s\n", input);

        if (get_letters(input) == 0) {
            len = get_others(input);
            printf("Andere Zeichen am Anfang: %ld\n", len);
        } else {
            len = get_letters(input);
            printf("Buchstaben am Anfang: %ld\n", len);
        }

        analyze_text(input);

        printf("--------------------------\n");
        prog_end = char_check();                    // check if programm should end
        if (prog_end == 'n') {
            printf("\n------PROGRAMM-ENDE-------");
            break;
        }
        fflush(stdin);
    }
    return 0;
}

void my_getline(char input[], long len){

    fgets(input, len, stdin);
    fflush(stdin);
    input[len]= '\0';
    /*
   char c;
   for(int i=0; i<len-1; i++){
       c = getchar();
       if (c != '\n'){
           input[i] = c;
       }
       else{
           break;
       }
   }
    */
}

long get_letters(char text[]){

    int len = 0;
    if (isalpha(text[0]) == 0){
        return 0;
    }
    else{
        len++;
        for (int i=1; i <=strlen(text); i++ ){
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
    if (isalpha(text[0]) != 0 && isspace(text[0]) == 0){
        return 0;
    }
    else{
        len++;
        for (int i=1; i <=strlen(text); i++ ){
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

    char end_char;
    printf("Nochmal (y|n)? ");
    fflush(stdin);
    end_char = getchar();

    while (end_char != 'y' && end_char != 'n'){
        printf("Bitte geben Sie 'y' oder 'n' ein!\n");
        printf("Nochmal (y|n)? ");
        fflush(stdin);
        end_char = getchar();
    }
    return end_char;
}

void analyze_text(char text[]) {

    int wrd_flag;
    int len;
    int wrd_count = 0;
    char stats[10] = {0};
    char cpy_text[N] = {0};

    if (get_letters(text) > 0) {             //check ob am anfang ein wort ist
        len = get_letters(text);
        wrd_flag = 1;
        if (get_letters(text) >= 10){       //zählt ein feld im stats array +1
            stats[9]++;
        }
        else{
            stats[get_letters(text)-1]++;
        }
    }
    else {
        len = get_others(text);
        wrd_flag = 0;
    }

    while (len <= strlen(text)) {       //loop unti len reaches the max value
        for (int i = 0;
             i <= strlen(text); i++) {  //copiert text von [len] bis [max(text)] in cpy_text(pos [0] bis [N-len])
            cpy_text[i] = text[i + len];
        }
        for (int i = strlen(text) + 1; i < N; i++) {     //füllt cpy_text von [len] bis [N] mit 0
            cpy_text[i] = 0;
        }
        if (wrd_flag == 1) {                 //check ob der letzte bereich ein wort war
            len += get_others(cpy_text);
            wrd_flag = 0;
            wrd_count++;
        }
        else {
            if (get_letters(cpy_text) >= 10) {
                stats[9]++;
            }
            else {
                stats[get_letters(cpy_text)-1]++;
            }
            len += get_letters(cpy_text);
            wrd_flag = 1;
        }
    }
        printf("Wortanzahl: %d\t\t\n", wrd_count);
         for (int i = 1; i <= 10; i++) {
             printf("Laenge: %d\t | \tHaefigkeit: %d\n", i, stats[i-1]);
         }
}
