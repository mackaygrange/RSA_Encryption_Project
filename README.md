# RSA Encryption Project

A WebAssembly-based implementation of the RSA public-key cryptosystem, providing secure encryption and digital signatures in the browser.

## Overview

This project implements the RSA (Rivest-Shamir-Adleman) cryptographic algorithm, compiled to WebAssembly for high-performance asymmetric encryption operations. It supports key generation, encryption, and decryption with configurable key sizes.

## Features

- **WebAssembly Implementation** - Native performance in the browser via WASM compilation
- **RSA Key Generation** - Generate public/private key pairs
- **Asymmetric Encryption** - Secure message encryption with public keys
- **Decryption** - Private key decryption operations
- **Configurable Key Sizes** - Support for various RSA key lengths
- **C++ Implementation** - High-performance cryptographic operations
- **Easy JavaScript Integration** - Simple wrapper for browser-based usage

## Project Structure

```
RSA_Encryption_Project/
├── src/
│   └── rsa_encryption.cpp  # RSA implementation
├── rsa_wrapper.cpp         # WebAssembly C++ wrapper
├── build_wasm.sh           # Linux/macOS build script
├── build_wasm.bat          # Windows build script
└── WASM_BUILD.md           # WebAssembly build documentation
```

## Building

### Prerequisites
- Emscripten SDK (for WebAssembly compilation)
- CMake (optional, for build configuration)
- C++11 or later compatible compiler

### Web Assembly Build

**Linux/macOS:**
```bash
./build_wasm.sh
```

**Windows:**
```bash
build_wasm.bat
```

The build output will generate:
- `rsa_demo.js` - JavaScript WASM loader
- `rsa_demo.wasm` - Compiled WebAssembly binary

For detailed build instructions, see [WASM_BUILD.md](WASM_BUILD.md)

## Usage

### Web Integration

```javascript
// Load WASM module
const wasmModule = await loadWasm('rsa_demo.wasm');

// Generate key pair
const keyPair = wasmModule.ccall(
  'rsa_generate_keypair',
  'string',
  ['number', 'number'],
  [keySize, exponent]
);

// Encrypt message with public key
const plaintext = "SECRET_MESSAGE";
const publicKey = keyPair.publicKey;
const ciphertext = wasmModule.ccall(
  'rsa_encrypt',
  'string',
  ['string', 'string'],
  [plaintext, publicKey]
);

// Decrypt with private key
const privateKey = keyPair.privateKey;
const decrypted = wasmModule.ccall(
  'rsa_decrypt',
  'string',
  ['string', 'string'],
  [ciphertext, privateKey]
);
```

## Algorithm Details

### Key Generation
- **Algorithm**: Probable prime generation with trial division
- **Public Exponent**: Configurable (typically 65537)
- **Modulus**: Product of two large prime numbers (n = p × q)
- **Private Exponent**: Calculated using extended Euclidean algorithm

### Encryption
1. Convert plaintext to integer m
2. Compute ciphertext: c ≡ m^e (mod n)
3. Where e is the public exponent

### Decryption
1. Convert ciphertext to integer c
2. Compute plaintext: m ≡ c^d (mod n)
3. Where d is the private exponent

### Security Properties
- **One-way function**: Computationally infeasible to factor n = p × q
- **Semantic security**: With proper padding (OAEP, PKCS#1 v1.5)
- **Deterministic** (without padding): Same plaintext produces same ciphertext

## Key Sizes & Performance

| Key Size | Generation Time | Encryption Speed | Security Level |
|----------|-----------------|------------------|-----------------|
| 512-bit | Very Fast | Very Fast | Minimal |
| 1024-bit | Fast | Fast | Weak |
| 2048-bit | Moderate | Moderate | Strong |
| 4096-bit | Slow | Slow | Very Strong |

⚠️ **512-bit and 1024-bit keys are cryptographically broken.** Use 2048-bit or larger for any real security.

## Security Considerations

### Production Use
- **Use established libraries** (OpenSSL, libsodium) for production systems
- **Proper padding schemes** (OAEP) essential for semantic security
- **Secure random generation** critical for key generation
- **Regular security audits** recommended for sensitive applications

### Browser Limitations
- **No true randomness**: Relies on browser's Crypto API
- **Performance constraints**: Large key operations may be slow
- **Memory usage**: RSA operations consume significant memory
- **Side-channel attacks**: Browser environment not protected from timing attacks

### This Implementation
- Educational and demonstration purposes
- NOT recommended for protecting sensitive real-world data
- Useful for learning cryptographic concepts
- Good for portfolio demonstration

## Integration in Portfolio

This project demonstrates:
- Asymmetric cryptography implementation
- Large number arithmetic (modular exponentiation)
- WebAssembly compilation and integration
- C++ to JavaScript interoperability
- Complex algorithm implementation

See the interactive demo at: [mackaygrange.com/projects](https://mackaygrange.com/#/projects)

## Mathematical Background

### Fundamental Problem
Finding factors of large numbers (factorization problem):
- Given n = p × q, find p and q
- Current best algorithms (General Number Field Sieve) are exponential in bit length
- With 2048-bit keys, factorization is computationally infeasible

### Fermat's Little Theorem
```
If p is prime and gcd(a, p) = 1:
  a^(p-1) ≡ 1 (mod p)
```

### RSA Key Property
```
m^(ed) ≡ m (mod n)
where e × d ≡ 1 (mod φ(n))
```

## References

- [RSA Cryptosystem (Wikipedia)](https://en.wikipedia.org/wiki/RSA_(cryptosystem))
- [PKCS #1: RSA Cryptography Specifications](https://tools.ietf.org/html/rfc8017)
- [Applied Cryptography - Schneier](https://www.schneier.com/books/applied_cryptography/)

## License

This implementation is provided as-is for educational purposes.

## Author

Mackay Grange - [Portfolio](https://mackaygrange.com)
