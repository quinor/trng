#include <cstdio>
#include "trng.hh"

using namespace TR;


int main ()
{
    TRNG trng;
    Node root = trng.get_root();

    printf("%-20s%llx\n", "root", root.u64());
    printf("%-20s%llx\n", "root[0]", root[0].u64());
    printf("%-20s%llx\n", "root[1]", root[1].u64());
    printf("%-20s%llx\n", "root[3]", root[3].u64());
    printf("%-20s%llx\n", "root[\"foo\"]", root["foo"].u64());

    printf("%-20s%llx\n", "root[0][3]", root[0][3].u64());
    printf("%-20s%llx\n", "root[1][3]", root[1][3].u64());
    printf("%-20s%llx\n", "root[\"bar\"][3]", root["bar"][3].u64());
    printf("%-20s%llx\n", "root[3][1][4][1]", root[3][1][4][1].u64());

}