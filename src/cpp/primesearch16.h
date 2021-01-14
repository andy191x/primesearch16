
#include <random>
#include <stdint.h>


class PrimeSearch16
{
public:

    //
    // Class constants
    //

    static const int MAX_RANGE = 65535;

private:

    //
    // Private data
    //

    static const int prime_array[320];

    int range;
    int prime;
    int skip;
    int pos;
    int query;

public:

    //
    // Public routines
    //

    PrimeSearch16();
    virtual ~PrimeSearch16();

    bool start(int max);
    int next();

private:

    //
    // Private routines
    //

    void clearState();
    int findNextPrime(int num);
    int random(int min, int max);
};
