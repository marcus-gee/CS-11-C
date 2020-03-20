#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* This function retruns the numeric day on which Easter falls on. If 
 * the number is lead with a negative sign, it means the day falls in 
 * March. If not, the day falls in April. */
int calculate_Easter_date(int year) {
    int golden_year;
    int century;
    int skipped_leap_years;
    int correction_factor;
    int sunday;
    int epact;
    int next_sunday;
    int date;
    
    /* outside allowable range */
    if (year < 1582 || year > 39999) {
        return 0;
    } else {
        golden_year = (year % 19) + 1;
        century = (year / 100) + 1;
        skipped_leap_years = ((3 * century) / 4) - 12;
        correction_factor = (((8 * century)+ 5) / 25) - 5;
        sunday = ((5 * year) / 4) - skipped_leap_years - 10;
        epact = ((11 * golden_year) + 20 + correction_factor - \
        skipped_leap_years) % 30;
    
        if ((epact == 25 && golden_year > 11) || (epact == 24)) {
            epact++;
        }
        next_sunday = 44 - epact;
        next_sunday = next_sunday < 21 ? next_sunday + 30 : next_sunday;
        next_sunday = next_sunday + 7 - ((sunday + next_sunday) % 7);
        if (next_sunday > 31) {
            date = next_sunday - 31;
        } else {
            date = -next_sunday;
        }
    }
    return date;
}

/* main runs the calculate_Easter_date() function from above 
 * and prints the month and day that Easter will fall on for a given 
 * year. If the year input into the function is outside the allowable 
 * range of years, it prints an error message. */
int main(void) {
    int day; 
    int year;
    int input;
    
    while (1) {
        input = scanf("%d", &year);
        if (input == EOF) {
             break;
        } else {
             day = calculate_Easter_date(year);
             if (day > 0) {
                 printf("%d - April %d\n", year, day);
             } else if (day < 0) {
                 printf("%d - March %d\n", year, -day);
             } else {
                 fprintf(stderr, "year is outside allowable range\n");
             }
        }
    }
    return 0;   
}
