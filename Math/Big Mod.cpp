
// Iterative
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



// Recursive
long long bigmod ( long long a, int p, long long m ) // finds a^p % m
{
    if ( p == 0 ) return 1; // If power is 0 ( a ^ 0 ), return 1
 
    if ( p & 1 ) // If power is odd
    {
        return ( ( a % m ) * ( bigmod ( a, p - 1, m ) ) ) % m;
    }
    else
    {
        long long tmp = bigmod ( a, p / 2, m ); 
        return ( tmp * tmp ) % m;
    }
}
