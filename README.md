# TRNG
tree-like rng for gamedev applications. Behaves like a `json`-like structure
with random values in every node. Mixing integer and string keys will result in
a runtime error (exception thrown).


## Example
```
root.u64()                3b2c8aefd44be966
root[0].u64()             d28b1dc8bd364bab
root[1].u64()             d7a2756ea4d7570c
root[2].u64()             bdec7adcd3c7ea3c
root[2]["foo"] .u64()     a2fa7d19fdd4accf
root[0][3].u64()          a4c48a81aef5fb92
root[1][3].u64()          4a4d43fc8f51179b
root[2]["bar"][3].u64()   265a8341d299e669
root[3][1][4][1].u64()    a56fc7ebeeed6c21
root[42].u64()            e4eee199af6a0ea0
root[42].reshuffle()      reshuffle
root[42].u64()            1bcf06cd0587fb16
```

## Compilation
Simply compile `trng.cc` and include `trng.hh`. Requires `--std=c++20` and `-lcrypto`.
