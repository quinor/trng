# TRNG
Stateless tree-like rng for gamedev applications. Behaves as a `json`-like
structure with random values in every node dependent only on the seed and
the path. Mixing integer and string keys is not recommended will result
in a safeguard runtime error (exception thrown) or possibly RNG values
repeating if the safeguard is bypassed!


## Example

Or read and run `main.cc`
```
root.u64()                3b2c8aefd44be966

// every node is both an rng value and a tree node
root[0].u64()             d28b1dc8bd364bab
root[1].u64()             d7a2756ea4d7570c
root[2].u64()             bdec7adcd3c7ea3c

// persistent values!
root[0].u64()             d28b1dc8bd364bab

// string accessors
root[2]["foo"].u64()      a2fa7d19fdd4accf
root[0][3].u64()          a4c48a81aef5fb92
root[1][3].u64()          4a4d43fc8f51179b

// mixing strings and integers
root[2]["bar"][3].u64()   265a8341d299e669

// unlimited (and almost performance free) levels
root[3][1][4][1].u64()    a56fc7ebeeed6c21

// persistent in arbitrarily deep paths
root[0][3].u64()          a4c48a81aef5fb92

// reshuffling of subtrees
root[42].u64()            e4eee199af6a0ea0
root[42].reshuffle()      reshuffle
root[42].u64()            1bcf06cd0587fb16
```

## Compilation
Simply compile and link to your project `trng.cc` and include `trng.hh`.
Requires `--std=c++20` and `-lcrypto`.
