# Forty Years of Attacks on the RSA Cryptosystem
Implementation of many attacks on the RSA cryptosystem written in C++, with some extra utilities written in Python.

## Attacks to implement:
### Attacks on RSA encryption, decryption and padding
* Small public exponent attack for `m < n^(1/e)`.
* Coppersmith's attack for stereotyped messages (given that you know all but `a` bits of the ciphertext, find those `a` bits if `a < len(n)/e`).
* Decryption oracle attack.
* Hastad's broadcast attack.
* Franklin-Reiter related message attack, along with Coppersmith's extension for short pads.
* Bleichenbacher's padding oracle attack.
* Parity oracle attack.

### Attacks on RSA signatures
* Blinding attack (from the signature `S'` of `m*r^e` calculate the signature `S = S'/r` of `m`.
* Fault attacks.

### Attacks on the modulus (attacks in which a private key can be derived from a public key)
* Common modulus attack (given one private key `p1` and one public key `p2`, both of the same modulus, calculate the associated private key for `p2`).
* Boneh-Durfee attack (if an RSA key has a private exponent `d < n^0.292`, calculate this exponent from the public key).
* Coppersmith's attack for factoring with high bits known.
* Fermat factoring attack for `p - q < n^(1/4)`.
* ROCA.

### Attacks for non-standard RSA
* Factoring for multi-prime RSA.
* Factoring for RSA over a polynomial quotient ring.
