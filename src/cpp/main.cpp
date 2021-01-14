
#include <iostream>
#include "primesearch16.h"

void printSets(int max, int count);
void validateSet(int max);

int main()
{
    //srand(1);
    srand(time(NULL));

    printf("Generating example sets:\n");
    printf("\n");
    printSets(4, 10);
    printf("\n");
    printSets(8, 10);
    printf("\n");
    printSets(16, 10);
    printf("\n");
    printSets(32, 10);
    printf("\n");
    printSets(100, 5);
    printf("\n");
    printSets(PrimeSearch16::MAX_RANGE, 1);
    printf("\n");
    printf("\n");

    printf("Checking integrity:\n");

    for (int i = 1; i < PrimeSearch16::MAX_RANGE; i++)
    {
        validateSet(i);
    }

    printf("\n");
    printf("\n");

    printf("done.\n");

    return 0;
}

void printSets(int max, int count)
{
    if (max < 1 || count < 1)
    {
        return;
    }

    for (int i = 0; i < count; i++)
    {
        PrimeSearch16 ps;
        ps.start(max);

        int cur = 0;
        bool first = true;
        while ((cur = ps.next()) != -1)
        {
            if (!first)
            {
                printf(", ");
            }
            printf("%d", cur);
            first = false;
        }
        printf("\n");
    }
}

void validateSet(int max)
{
    if (max % 1000 == 0)
    {
        printf("%d...\n", max);
    }

    PrimeSearch16 ps;
    ps.start(max);

    bool* found = new bool[max];
    for (int i = 0; i < max; i++)
    {
        found[i] = false;
    }

    int next = 0;
    while (next != -1)
    {
        next = ps.next();
        if (next >= max)
        {
            printf("%d: Invalid \"next\" value: %d\n", max, next);
        }
        if (next == -1)
        {
            break;
        }

        found[next] = true;
    }

    for (int i = 0; i < max; i++)
    {
        if (!found[i])
        {
            printf("%d: Never generated: %d\n", max, i);
            break;
        }
    }

    delete[] found;
}
