
vector<int> primes; // stores prime numbers

void sieve(int n) // finds all primes till n; including n
{
    bool mark[n+5]; // (mark[i] == false) for all prime i; initially mark[] is set to false
    memset(mark, false, sizeof mark);

    mark[1] = true;
    for(int i=4; i<=n; i+=2) mark[i] = true;

    primes.push_back(2);

    int rt = sqrt(n) + 2;
    for(int i=3; i<=n; i+=2){
        if(!mark[i]){
            primes.push_back(i);
            if(i <= rt){
                for(int j=i*i; j<=n; j += 2*i) mark[j] = true;
            }
        }
    }
}
