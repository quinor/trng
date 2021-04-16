#include <cstdio>
#include "trng.hh"

using namespace TR;


int main ()
{
    TRNG trng(1337); // seed optional!
    Node root = trng.get_root();

    printf("%-20s%llx\n", "root", root.u64());

    // node can be simultanousely used as an rng and for its children
    printf("%-20s%llx\n", "root[0]", root[0].u64());
    printf("%-20s%llx\n", "root[1]", root[1].u64());
    printf("%-20s%llx\n", "root[2]", root[3].u64());

    // string and int identifiers cannot be mixed in [] accessors of a given node
    // (it may result in rng values repeating). Some checks are in place to safeguard
    // so for example root["bar"] would fail.
    printf("%-20s%llx\n", "root[2][\"foo\"]", root[3]["foo"].u64());

    // multi-level access
    printf("%-20s%llx\n", "root[0][3]", root[0][3].u64());
    printf("%-20s%llx\n", "root[1][3]", root[1][3].u64());
    printf("%-20s%llx\n", "root[2][\"bar\"][3]", root[1]["bar"][3].u64());
    printf("%-20s%llx\n", "root[3][1][4][1]", root[3][1][4][1].u64());

    // reshuffling persistently changes node's rng
    printf("%-20s%llx\n", "root[42]", root[42].u64());
    root[42].reshuffle();
    printf("%-20sreshuffle\n", "root[42]");
    printf("%-20s%llx\n", "root[42]", root[42].u64());
    return 0;
}