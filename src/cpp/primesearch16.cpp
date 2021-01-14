
#include "primesearch16.h"

const int PrimeSearch16::prime_array[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
    89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
    181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 307, 401, 503, 701, 809, 907,
    1009, 1303, 1511, 1753, 2003, 2251, 2503, 2753, 3001, 3251, 3511, 3761, 4001, 4253, 4507, 4751, 5003,
    5261, 5501, 5779, 6007, 6257, 6521, 6761, 7001, 7253, 7507, 7753, 8009, 8263, 8501, 8753, 9001, 9257,
    9511, 9767, 10007, 10253, 10501, 10753, 11003, 11251, 11503, 11777, 12007, 12251, 12503, 12757, 13001,
    13513, 13751, 14009, 14251, 14503, 14753, 15013, 15259, 15511, 15761, 16001, 16253, 16519, 16759, 17011,
    17257, 17509, 17761, 18013, 18251, 18503, 18757, 19001, 19259, 19501, 19751, 20011, 20261, 20507, 20753,
    21001, 21269, 21503, 21751, 22003, 22259, 22501, 22751, 23003, 23251, 23509, 23753, 24001, 24251, 24763,
    25013, 25253, 25523, 25759, 26003, 26251, 26501, 26759, 27011, 27253, 27509, 27751, 28001, 28277, 28513,
    28751, 29009, 29251, 29501, 29753, 30011, 30253, 30509, 30757, 31013, 31253, 31511, 31751, 32003, 32251,
    32503, 32771, 33013, 33287, 33503, 33751, 34019, 34253, 34501, 34757, 35023, 35251, 35507, 35753, 36007,
    36251, 36523, 36761, 37003, 37253, 37501, 37781, 38011, 38261, 38501, 38767, 39019, 39251, 39503, 39761,
    40009, 40253, 40507, 40751, 41011, 41257, 41507, 41759, 42013, 42257, 42509, 42751, 43003, 43261, 43517,
    43753, 44017, 44257, 44501, 44753, 45007, 45259, 45503, 45751, 46021, 46261, 46507, 46751, 47017, 47251,
    47501, 47777, 48017, 48259, 48523, 48751, 49003, 49253, 49523, 49757, 50021, 50261, 50503, 50753, 51001,
    51257, 51503, 51767, 52009, 52253, 52501, 52757, 53003, 53267, 53503, 53759, 54001, 54251, 54503, 54751,
    55001, 55259, 55501, 55763, 56003, 56501, 56767, 57037, 57251, 57503, 57751, 58013, 58271, 58511, 58757,
    59009, 59263, 59509, 59753, 60013, 60251, 60509, 60757, 61001, 61253, 61507, 61751, 62003, 62273, 62501,
    62753, 63029, 63277, 63521, 64007, 64271, 64513, 64763, 65003, 65257, 65519, 65537, 65539, 65543, 65551
};

PrimeSearch16::PrimeSearch16()
{
    this->clearState();
}

PrimeSearch16::~PrimeSearch16()
{

}

/*
 * @param max - Maximum search range. Valid range is 1 to PrimeSearch16::MAX_RANGE.
 * @return - Whether or not search started.
 */
bool PrimeSearch16::start(int max)
{
    this->clearState();

    if (max <= 0 || max > PrimeSearch16::MAX_RANGE)
    {
        return false;
    }

    range = max;
    prime = this->findNextPrime(range);
    skip = this->random(1000000, 2000000); // used to make the results appear "random"
    //skip = 1;

    if (skip % prime == 0)
    {
        skip++;
    }

    pos = this->random(0, range - 1); // used to randomize the starting point
    //pos = 0;

    return true;
}

/*
 * @return - Next number in sequence or -1 if sequence is complete.
 */
int PrimeSearch16::next()
{
    if (query == range)
    {
        return -1;
    }

    int next = pos;

    while (true)
    {
        next += skip;
        next %= prime;

        if (next < range)
        {
            pos = next;
            break;
        }
        else
        {
            // This overhead is the tradeoff from the "skip randomness".
            // It will be entered X times during the set iteration, where X is the difference between the chosen prime and the set size.
        }
    }

    query++;
    return pos;
}

void PrimeSearch16::clearState()
{
    range = 0;
    prime = 0;
    skip = 0;
    pos = 0;
    query = 0;
}

int PrimeSearch16::findNextPrime(int num)
{
    int prime_len = sizeof(prime_array) / sizeof(int);

    for (int i = 0; i < prime_len; i++)
    {
        if (prime_array[i] > num)
        {
            return prime_array[i];
        }
    }

    return 0;
}

int PrimeSearch16::random(int min, int max)
{
    if (min == max)
    {
        return min;
    }

    return min + (rand() % (max - min));
}
