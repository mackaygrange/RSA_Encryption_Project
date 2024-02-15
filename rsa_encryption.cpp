#include <iostream>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <numeric>
#include <cmath>

int validate_prime(int n)
{
    if (n <= 1)
    {
        std::cout << "Error, the integer must be prime. " << n << " is not a prime number." << std::endl;
        return 0;
    }

    for (unsigned int i = 2; i <= (n / 2); i++)
    {
        if (n % i == 0)
        {
            std::cout << "Error, the integer must be prime. " << n << " is not a prime number." << std::endl;
            return 0;
        }
    }

    return n;
}

int find_gcd(int e, int lambda)
{
    if (lambda == 0)
        return lambda;
    return find_gcd(lambda, e % lambda);   
}

int validate_e(int e, int lambda)
{
    if (e < 3 || e >= lambda)
    {
        std::cout << "Invalid lambda value. Value e must be between 3 and lambda - 1." << std::endl;
        return 0;
    }
    else if (find_gcd(e, lambda != 1))
    {
        std::cout << "Invalid lambda value. Values e and lambda must be coprime." << std::endl;
        return 0;
    }
    else
    {
        return e;
    }
}

int find_d(int e, int lambda)
{
    int d;
    for (unsigned int i = 1; i < lambda; i++)
    {
        d = i * e;
        if (d % lambda == 1)
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
    int p = 0;
    int q = 0;
    int t = 0;

    while (!p)
    {
        std::cout << "Enter Prime Value \'p\': " << std::endl;
        std::cin >> t;
        p = validate_prime(t);
        std::cout << std::endl;
    }

    while (!q)
    {
        std::cout << "Enter Prime Value \'q\': " << std::endl;
        std::cin >> t;
        q = validate_prime(t);
        std::cout << std::endl;
    }

    int n = p * q;
    int lambda = (p - 1) * (q - 1);

    std::cout << "Value of \'n\': " << n << std::endl;
    std::cout << "Value of \'lambda(n)\': " << lambda << std::endl;
    std::cout << std::endl;

    int e = 0;

    while (!e)
    {
        std::cout << "Enter Value \'e\': " << std::endl;
        std::cin >> t;
        e = validate_e(t, lambda);
        std::cout << std::endl;
    }
    
    int d = find_d(e, lambda);
    std::cout << "Value of \'d\': " << d << std::endl;
    std::cout << std::endl;

    public_key.push_back(n);
    private_key.push_back(n);
    public_key.push_back(e);
    private_key.push_back(d);

    std::cout << "Public Key: {" << public_key.at(0) << ", " << public_key.at(1) << "}" << std::endl;
    std::cout << "Private Key: {" << private_key.at(0) << ", " << private_key.at(1) << "}" << std::endl;
    std::cout << std::endl;

    int m;
    std::cout << "Enter plaintext integer value \'m\': " << std::endl;
    std::cin >> m;
    std::cout << std::endl;

    long double c = (long double) std::pow(m, public_key.at(1));
    c = (unsigned long long int) c % public_key.at(0);
    std::cout << "Encrypted Value of \'m\' (c): " << c << std::endl;
    std::cout << std::endl;

    long double m2 = (long double) std::pow(c, private_key.at(1));
    m2 = (unsigned long long int) m2 % private_key.at(0);
    std::cout << "Unencrypted Value of \'m\' (m2): " << m2 << std::endl;
    std::cout << std::endl;

    return 0;
}