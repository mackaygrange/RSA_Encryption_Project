#include <iostream>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <numeric>
#include <cmath>

int get_gcd(int e, int lambda)
{
    if (lambda == 0)
        return e;
    return get_gcd(lambda, e % lambda);   
}

int get_lcm(int phi_p, int phi_q) 
{
    return (phi_p * phi_q) / get_gcd(phi_p, phi_q);
}

int get_d(int e, int lambda)
{
    int d;
    for (unsigned int i = 1; i < lambda; i++)
    {
        d = i * e;
        if (d % lambda == 1 && i != e)
        {
            return i;
        }
    }
    return 0;
}

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

int validate_e(int e, int lambda)
{
    if (e < 3 || e >= lambda)
    {
        std::cout << "Invalid lambda value. Value e must be between 3 and lambda - 1." << std::endl;
        return 0;
    }
    else if (get_gcd(e, lambda) != 1)
    {
        std::cout << "Invalid lambda value. Values e and lambda must be coprime." << std::endl;
        return 0;
    }
    else
    {
        return e;
    }
}

unsigned long long int encrypt(int m, int e, int n)
{
    unsigned long long int x = 1, y = m;
    while (e > 0)
    {
        if (e % 2 == 1)
        {
            x = (x * y) % n;
        }
        y = (y * y) % n;
        e /= 2;
    }
    return x % n;
}

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
    int lambda = get_lcm((p - 1), (q - 1));

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
    
    int d = get_d(e, lambda);
    std::cout << "Value of \'d\': " << d << std::endl;
    std::cout << std::endl;

    std::cout << "Public Key: {" << n << ", " << e << "}" << std::endl;
    std::cout << "Private Key: {" << n << ", " << d << "}" << std::endl;
    std::cout << std::endl;

    unsigned long long int m;
    std::cout << "Enter plaintext integer value \'m\': " << std::endl;
    std::cin >> m;
    std::cout << std::endl;

    unsigned long long int c = encrypt(m, e, n);
    std::cout << "Encrypted Value of \'m\' (c): " << c << std::endl;
    std::cout << std::endl;

    unsigned long long int m2 = encrypt(c, d, n);
    std::cout << "Unencrypted Value of \'m\' (m2): " << m2 << std::endl;
    std::cout << std::endl;

    return 0;
}
