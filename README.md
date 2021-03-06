# Forty Years of Attacks on the RSA Cryptosystem
Implementation of many attacks on the RSA cryptosystem written in C++, with some extra utilities written in Python.

## Attacks to implement:
### Attacks on RSA encryption, decryption and padding
- [X] ~~Small public exponent attack for `m < n^(1/e)`.~~ Implemented in `integer_root.cpp`.
- [ ] Hastad's broadcast attack.
- [X] ~~Common modulus attack for external attacker (given two ciphertexts of a message `m` encrypted with one of two public keys `<n, e1>` and `<n, e2>` which have a common modulus, calculate `m`).~~ Implemented in `common_modulus_external.cpp`.
- [ ] Coppersmith's attack for stereotyped messages (given that you know all but `a` bits of the ciphertext, find those `a` bits if `a < len(n)/e`).
- [ ] Franklin-Reiter related message attack, along with Coppersmith's extension for short pads.

### Attacks on RSA signatures
- [X] ~~Blinding attack (from the signature `S'` of `m*r^e` calculate the signature `S = S'/r` of `m`.~~ Implemented in `blinding.cpp`.

### Attacks on the modulus (attacks in which a private key can be derived from a public key)
- [X] ~~Common modulus attack for internal attacker (given one private key `p1` and one public key `p2`, both of the same modulus, calculate the associated private key for `p2`).~~ Implemented in `common_modulus.cpp`.
- [X] ~~Fermat factoring attack for `p - q < n^(1/4)`.~~ Implemented in `fermat_factor.cpp`.
- [ ] ECM factoring.
- [ ] Boneh-Durfee attack (if an RSA key has a private exponent `d < n^0.292`, calculate this exponent from the public key).
- [ ] Coppersmith's attack for factoring with high bits known.
- [ ] ROCA.

### Attacks for non-standard RSA
- [ ] Factoring for multi-prime RSA.
- [ ] Factoring for RSA over a polynomial quotient ring.

## Helper scripts to make
- [ ] Python scripts for easy input (input messages as hex, strings, base-10, etc.)
