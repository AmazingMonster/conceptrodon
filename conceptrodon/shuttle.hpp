// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SHUTTLE_H
#define CONCEPTRODON_SHUTTLE_H

#include <utility>

namespace Conceptrodon {

/******************************************************************************************************/
template<auto...Variables>
struct Shuttle
{
    static constexpr size_t size() { return sizeof...(Variables); }

    template<template<auto...> class Sequence>
    struct Detail { using type = Sequence<Variables...>; };

    template<template<auto...> class...Sequences>
    using Rail = Detail<Sequences...>::type;

    template<template<auto...> class Sequence>
    using UniRail = Sequence<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
template<size_t...Indices>
struct Shuttle<Indices...>
: public std::index_sequence<Indices...>
{
    template<template<auto...> class Sequence>
    struct ProtoRail { using type = Sequence<Indices...>; };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>::type;

    template<template<auto...> class Sequence>
    using UniRail = Sequence<Indices...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
template<size_t...Indices>
using Ark = Shuttle<Indices...>;

template<std::make_signed_t<size_t>...Indices>
using SignedArk = Shuttle<Indices...>;
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
struct Digon: public Shuttle<I, J>
{
    static constexpr auto first() { return I; }
    static constexpr auto second() { return J; }
};
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J, auto K>
struct Trigon: public Shuttle<I, J, K>
{
    static constexpr auto first() { return I; }
    static constexpr auto second() { return J; }
    static constexpr auto third() { return K; }
};
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J, auto K, auto L>
struct Tetragon: public Shuttle<I, J, K, L>
{
    static constexpr auto first() { return I; }
    static constexpr auto second() { return J; }
    static constexpr auto third() { return K; }
    static constexpr auto fourth() { return L; }
};
/******************************************************************************************************/

}

#endif