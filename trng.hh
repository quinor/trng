#pragma once

#include <cstdint>
#include <cstddef>

#include <vector>
#include <string>
#include <unordered_map>


namespace TR {


// internal rng sate; wrapper for plain 128 bits.
struct RNGState
{
    union {
        uint8_t i8[16];
        uint64_t i64[2];
    };
};

static_assert(sizeof(RNGState) == 16, "RNGState's binary layout not continuous");


// TRNG's internal rng class. Performs aes and provides a basic interface.
class InternalRNG
{
public:
    // constructors
    InternalRNG(uint64_t);
    InternalRNG(RNGState);

    // value accessors
    uint64_t get_id() const;
    uint64_t get_value(uint64_t) const;
    InternalRNG descend(int64_t) const;
    // void reshuffle();

private:
    RNGState key;
    RNGState aes(RNGState) const;
    // uint64_t revision;
};



// forward declarations
class TRNG;
class Node;


class Node
{
public:
    // constructors
    Node(InternalRNG, TRNG*, uint64_t);

    // tree descenders
    Node operator[](const std::string&) const;
    Node operator[](int64_t) const;

    // value getters
    // single
    uint64_t u64() const;
    int64_t randint(int64_t min, int64_t max) const;
    double uniform(double min=0, double max=1) const;

    // multi
    std::vector<uint64_t>&& u64s(size_t) const;
    std::vector<int64_t>&& randints(size_t, int64_t min, int64_t max) const;
    std::vector<double>&& uniforms(size_t size, double min=0, double max=1) const;

private:
    InternalRNG rng;
    TRNG* head;
    uint64_t id;
    // runtime flag [int] vs [string]?
};


class TRNG
{
public:
    // constructors
    explicit TRNG(uint64_t seed=0);
    Node get_root();
    uint64_t str_idx(const std::string&);

private:
    Node root;
    uint64_t ctr;
    std::unordered_map<std::string, uint64_t> string_indexes;
};


// TODO: how to make the structure modifiable, preferably without affecting the size too much?


} // namespace TRNG
