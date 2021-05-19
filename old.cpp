#include <stdio.h>


long readNumber();
long isPrime(long num);
char charCheck();
void primeFactors(long num);
long isPrimeFast(long num);
void expandNumber(long num);


int main() {


    long number;                                        // init
    int prime_stat;


    while (1) {

        number = readNumber();                          // input of the number
        if (number < 100)                              // check if isPrime or isPrimeFast is used
            prime_stat = isPrimeFast(number);
        else
            prime_stat = isPrime(number);

        if (prime_stat == -1){       // output for non prime numbers
            printf("%ld ist negativ oder 0 und damit nicht Prim!\n", number);
        }
        else if(prime_stat == 0){
            printf("%ld ist nicht Prim!\n", number);
            primeFactors(number);
        }
        else if (prime_stat == 1)                       // output for prime numbers
            printf("%ld ist Prim!\n", number);
        else
            printf("Ein Fehler ist aufgetreten!\n");

        if (number > 2 && number % 2 == 0)              // output for Goldbach-conjecture
            expandNumber(number);

        printf("--------------------------\n");
        char prog_end = charCheck();                    // check if programm should end
        if (prog_end == 'n'){
            printf("\n------PROGRAMM-ENDE-------");
            break;
        }
    }
    return 0;
}


long readNumber() {
    // gets number as input, checks if it's a long and returns the number

    long num;
    char term;
    while (1) {
        printf("Bitte geben Sie eine ganze Zahl ein: ");
        if (scanf("%ld%c", &num, &term) != 2 || term != '\n'){
            printf("Fehler bei Zahleneingabe!\n");
            fflush(stdin);
        }
        else
            break;
    }
    return num;
}


long isPrime (long num){
    // checks if the number is a prime and returns a 1 if it is

    if (num <= 0){
        return -1;
    }
    else if (num == 1){
        return 0;
    }
    else {
        for (long i = 2; i * i <= num; i++){
            if (num % i == 0)
                return 0;
        }
        return 1;
    }
}


char charCheck(){
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


void primeFactors(long num){
    // prints out the prime factors of a number

    if (num > 1) {
        printf("Primfaktorzerlegung: %ld = ", num);
        for (long i = 2; i <= num; i++) {
            while (num % i == 0) {
                printf(" %ld *", i);
                num = num / i;
            }
        }
        printf("\b \n");
    }
}


long isPrimeFast(long num){
// init PrimeArray the first time it runs, then returns 1 if num is a prime
    static int fr_flag = 0;
    static long PrimeArray[100] = {};

    if (num == 1)
        return 0;
    else if (num <= 0)
        return -1;
    else {
        if (fr_flag == 0) {
            for (int i = 0; i < 100; i++) {
                PrimeArray[i] = isPrime(i);
            }
            fr_flag = 1;
        }
        return PrimeArray[num];
    }
}


void expandNumber(long num){
    // prints out the Goldbach-conjecture of a even number

    for(unsigned long i = 2; i < num; i++) {
        if (num < 100) {
            if (isPrimeFast(i) == 1 && isPrimeFast(num - i) == 1) {
                printf("Goldbach-Zerlegung: %ld = %ld + %ld\n", num, i, num - i);
                break;
            }
        }
        else {
            if (isPrime(i) == 1 && isPrime(num - i) == 1) {
                printf("Goldbach-Zerlegung: %ld = %ld + %ld\n", num, i, num - i);
                break;
            }
        }
    }
}

/*long isPrimeFast(long num){
    // alt version of isPrimeFast with preset array

    static int PrimeArray[] = {
            3,  5,  7, 11, 13, 17, 19, 23,
            29, 31, 37, 41, 43, 47, 53, 59,
            61, 67, 71, 73, 79, 83, 89, 97
    };
    if (num == 1)
        return 0;
    else if (num <= 0)
        return -1;
    else {
        for (int i = 0; i <= sizeof(PrimeArray)/sizeof(long); i++) {
            if (num == PrimeArray[i]) {
                return 1;
            }
        }
        return 0;
    }

} */
