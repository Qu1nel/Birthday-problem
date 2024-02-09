#include <inttypes.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "calendar.h"
#include "print.h"

#define COUNT_SIMULATION 100000

size_t simulation_brithdays(Date** brithdays, const size_t count);
size_t get_number_of_days(void);

void print_brithdays(Date** brithdays, const size_t count);
void print_match(const Date* match);
void print_result(const size_t simulation_count, const size_t count);


int main(void)
{
    srand((unsigned)time(NULL));

    size_t num_of_days = get_number_of_days();

    Date** brithdays = get_brithdays(num_of_days);
    print_brithdays(brithdays, num_of_days);

    Date* match = get_match(brithdays, num_of_days);
    print_match(match);

    size_t simulation_match = simulation_brithdays(brithdays, num_of_days);
    print_result(simulation_match, num_of_days);

    return EXIT_SUCCESS;
}


size_t get_number_of_days(void)
{
    size_t var;

    while (true) {
        set_param_print("\n", "");
        print("How many birthdays shall I generate? (Max 100)", "> ");

        scanf_s("%zu", &var);

        if (0 < var and var <= 100) {
            break;
        }
    }
    set_param_print(" ", "\n");
    print("");

    return var;
}


void print_brithdays(Date** brithdays, const size_t count)
{
    print("Here are", count, "birthdays:");
    set_param_print(" ", "");
    for (size_t i = 0; i < count; ++i) {
        if (i != 0) {
            print(", ");
        }
        char* month_name = MONTHS[brithdays[i]->month - 1];
        print(month_name, brithdays[i]->day);
    }
    print("\n\n");
}


void print_match(const Date* match)
{
    print("In this simulation, ");
    print_end = "\n";
    if (match != NULL) {
        char* month_name = MONTHS[match->month - 1];
        print_sep = " ";
        print("multiple people have a birthday on", month_name, match->day);
    } else {
        print("there are no matching birthdays.");
    }
}


size_t simulation_brithdays(Date** brithdays, const size_t count)
{
    size_t result = 0;

    print("\nGenerating", count, "random birthdays", COUNT_SIMULATION, "times...\n");
    print("Let's run another", COUNT_SIMULATION, "simulations.\n");

    for (size_t i = 0; i < COUNT_SIMULATION; ++i) {
        if (i % (COUNT_SIMULATION / 10) == 0) {
            print(i, "simulation run...");
        }
        free_brithdays(brithdays, count);
        brithdays = get_brithdays(count);
        if (get_match(brithdays, count) != NULL) {
            result++;
        }
    }
    free_brithdays(brithdays, count);

    return result;
}


void print_result(const size_t simulation_match, const size_t count)
{
    double probability = (double)simulation_match / COUNT_SIMULATION * 100;
    print("\nout of", COUNT_SIMULATION, "simulations of", count, "people, there was a");
    print("matching birthday in that group", simulation_match, "times. this means");
    print("that", simulation_match, "people have a", probability, "% chance of");
    print("having a matching birthday in their group.");
    print("That's probably more than you would think!");
}
