//finding  (1 / a) % m

// if m is prime
long long bigmod ( long long a, long long p, long long m ) // finds a^p % m
{
    long long res = 1;
    long long x = a;

    while ( p )
    {
        if ( p & 1 ) //p is odd
        {
            res = ( res * x ) % m;
        }
        x = ( x * x ) % m;
        p = p >> 1;
    }

    return res;
}
long long modinverse(long long a, long long m) // caller function
{
    return bigmod(a, m-2, m);
}
