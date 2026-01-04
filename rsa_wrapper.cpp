#include <cstring>
#include <cstdio>

// Include the RSA implementation
#include "src/rsa_encryption.cpp"

// Exported functions for JavaScript
extern "C"
{
    // RSA_Encryption wrapper
    // Returns ciphertext as an integer string
    const char* rsa_encrypt(int p, int q, int e, int m)
    {
        try
        {
            unsigned long long int result = RSA_Encryption(p, q, e, m);

            char* output = new char[32];
            sprintf(output, "%llu", result);
            return output;
        }

        catch (...)
        {
            return "ERROR";
        }
    }

    // RSA_Decryption wrapper
    // Returns plaintext as an integer string
    const char* rsa_decrypt(int c, int d, int n)
    {
        try
        {
            unsigned long long int result = RSA_Decryption(c, d, n);

            char* output = new char[32];
            sprintf(output, "%llu", result);
            return output;
        }

        catch (...)
        {
            return "ERROR";
        }
    }

    // Utility: Calculate n from p and q
    int calculate_n(int p, int q)
    {
        return p * q;
    }

    // Utility: Calculate lambda from p and q
    int calculate_lambda(int p, int q)
    {
        return get_lcm((p - 1), (q - 1));
    }

    // Utility: Calculate d from e and lambda
    int calculate_d(int e, int lambda)
    {
        return get_d(e, lambda);
    }

    // Utility: Validate if a number is prime
    int is_prime(int n)
    {
        return validate_prime(n);
    }

    // Utility: Validate e value
    int validate_e_value(int e, int lambda)
    {
        return validate_e(e, lambda);
    }

    // Allocate memory
    char* allocate_memory(int size)
    {
        return new char[size];
    }

    // Free allocated memory
    void free_memory(char* ptr)
    {
        delete[] ptr;
    }
}
