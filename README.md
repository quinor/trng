# TRNG
tree-like rng for gamedev applications. Behaves like a `json`-like structure
with random values in every node.


## Example
```
root.u64()                3b2c8aefd44be966
root[0].u64()             d28b1dc8bd364bab
root[1].u64()             d7a2756ea4d7570c
root[3].u64()             bdec7adcd3c7ea3c
root["foo"].u64()         d28b1dc8bd364bab
root[0][3].u64()          a4c48a81aef5fb92
root[1][3].u64()          4a4d43fc8f51179b
root["bar"][3].u64()      4a4d43fc8f51179b
root[3][1][4][1].u64()    a56fc7ebeeed6c21
```

## Compilation
Simply compile `trng.cc` and include `trng.hh`. Requires `--std=c++20` and `-lcrypto`.
