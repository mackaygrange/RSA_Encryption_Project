#include <iostream>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <numeric>
#include <cmath>

bool prime_check(int n)
{
    if (n <= 1)
    {
        return false;
    }

    for (unsigned int i = 2; i <= (n / 2); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

int find_gcd(int e, int lambda)
{
    if (lambda == 0)
        return lambda;
    return find_gcd(lambda, e % lambda);   
}

int find_e(int z)
{
    int e;
    while (true)
    {
        e = (rand() % z) + 1;

        if (find_gcd(e, z) == 1)
        {
            return e;
        }
    }
    return 0;
}

int find_d(int e, int z)
{
    int d;
    for (unsigned int i = 1; i < z; i++)
    {
        d = i * e;
        if (d % z == 1)
        {
            if (i != e)
            {
                return i;
            }
        }   
    }
    return 0;
}

std::vector<int> public_key;
std::vector<int> private_key;

int main()
{
    int p;
    int q;

    std::cout << "Enter Prime Value \'p\':" << std::endl;
    std::cin >> p;
    std::cout << "Enter Prime Value \'q\':" << std::endl;
    std::cin >> q;

    int n = p * q;
    int lambda = (p - 1) * (q - 1); 
    int e;
    int d;

    return 0;
}