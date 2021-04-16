#include "trng.hh"

#include <openssl/aes.h>
#include <utility>

namespace TR {


static double u64_to_uniform01(uint64_t rnd) {
    uint64_t r = (rnd & 0xFFFFFFFFFFFFFull) | 0x3FF0000000000000ull;
    return *(double *)(&r) - 1.0;
}


// InternalRNG impl

RNGState InternalRNG::aes(RNGState in) const
{
    AES_KEY aes_key;
    RNGState out;

    AES_set_encrypt_key(key.i8, 128, &aes_key);
    AES_encrypt(in.i8, out.i8, &aes_key);
    return out;
}

InternalRNG::InternalRNG(uint64_t seed)
{
    key = {.i64={seed, 0}};
}

InternalRNG::InternalRNG(RNGState state)
: key(state)
{}

uint64_t InternalRNG::get_value(uint64_t idx) const
{
    RNGState state = {};
    state.i64[0] = idx;
    return aes(state).i64[0];
}

uint64_t InternalRNG::get_id() const
{
    RNGState state = {};
    RNGState ret = aes(state);
    return ret.i64[0] ^ ret.i64[1];
}

InternalRNG InternalRNG::descend(int64_t idx) const
{
    RNGState state = {};
    state.i64[0] = idx;
    return InternalRNG(aes(state));
}


// Node impl

Node::Node(InternalRNG rng_, TRNG* head_, uint64_t id_)
: rng(rng_)
, head(head_)
, id(id_)
{}

Node Node::operator[](int64_t idx) const
{
    return Node(rng.descend(idx), head, rng.get_id()^idx);
}

Node Node::operator[](const std::string& kwd) const
{
    return (*this)[head->str_idx(kwd)];
}

uint64_t Node::u64() const
{
    return rng.get_value(0);
}

int64_t Node::randint(int64_t min, int64_t max) const
{
    uint64_t range = max-min;
    return rng.get_value(0)%range + min;
}

double Node::uniform(double min, double max) const
{
    double range = max-min;
    return min + range*u64_to_uniform01(rng.get_value(0));
}

std::vector<uint64_t>&& Node::u64s(size_t size) const
{
    std::vector<uint64_t> ret;
    ret.resize(size);
    for (size_t i=0; i<size; i++)
        ret[i] = rng.get_value(i);
    return std::move(ret);
}

std::vector<int64_t>&& Node::randints(size_t size, int64_t min, int64_t max) const
{
    uint64_t range = max-min;
    std::vector<int64_t> ret;
    ret.resize(size);
    for (size_t i=0; i<size; i++)
        ret[i] = rng.get_value(i)%range + min;
    return std::move(ret);
}

std::vector<double>&& Node::uniforms(size_t size, double min, double max) const
{
    double range = max-min;
    std::vector<double> ret;
    ret.resize(size);
    for (size_t i=0; i<size; i++)
        ret[i] = min + range*u64_to_uniform01(rng.get_value(i));
    return std::move(ret);
}


// TRNG impl
TRNG::TRNG(uint64_t seed)
: root(InternalRNG(seed), this, 0)
, ctr(0)
{
}

uint64_t TRNG::str_idx(const std::string& str)
{
    if(!string_indexes.contains(str))
        string_indexes[str] = ctr++;
    return string_indexes[str];
}

Node TRNG::get_root()
{
    return root;
}



}; // namespace TRNG
