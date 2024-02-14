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

int find_gcd(int e, int z)
{
    if (z == 0)
        return e;
    return find_gcd(z, e % z);   
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

std::pair<std::vector<int>, std::vector<int>> generate_keys(int p, int q)
{
    std::vector<int> public_key;
    std::vector<int> private_key;
    int n;
    int z;
    int e;
    int d;

    srand(time(0));

    try
    {
        if (!prime_check(p))
        {
            throw (p);
        }
        
        if (!prime_check(q))
        {
            throw (q);
        }

    }

    catch (int non_prime)
    {
        std::cout << "Error, the following provided value is not prime: " << non_prime << std::endl;
        return std::make_pair(public_key, private_key);
    }

    n = p * q;
    z = (p - 1) * (q - 1);
    e = find_e(z);
    d = find_d(e, z);

    public_key.push_back(n);
    public_key.push_back(e);

    private_key.push_back(n);
    private_key.push_back(d);

    return std::make_pair(public_key, private_key);

}

double encrypt_plaintext(int plaintext, std::vector<int> key)
{
    return std::fmod(std::pow(plaintext, key.at(1)), key.at(0));
}

double decrypt_ciphertext(int ciphertext, std::vector<int> key)
{
    return (unsigned long long int(std::pow(ciphertext, key.at(1))) % key.at(0) );
}

int main()
{
    std::vector<int> public_key;
    std::vector<int> private_key;

    tie(public_key, private_key) = generate_keys(23, 97);

    std::cout << "Public Keys: " << public_key.at(0) << ", " << public_key.at(1) << std::endl;
    std::cout << "Private Keys: " << private_key.at(0) << ", " << private_key.at(1) << std::endl;

    int plaintext = 124;
    std::cout << "Plaintext: " << plaintext << std::endl;
    int ciphertext = encrypt_plaintext(plaintext, public_key);
    std::cout << "Ciphertext: " << ciphertext << std::endl;
    int plaintext_2 = decrypt_ciphertext(ciphertext, private_key);
    std::cout << "Back to Plaintext: " << plaintext_2 << std::endl;


    return 0;
}