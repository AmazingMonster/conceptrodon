// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SHUTTLE_H
#define CONCEPTRODON_SHUTTLE_H

#include <utility>

namespace Conceptrodon {
    

    
    
/******************************************************************************************************/
template<auto...Variables>
struct Payload
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
template<auto...>
struct Payroll {};

template<auto First, auto...Others>
struct Payroll<First, Others...>
{
    static constexpr auto first() { return First; }
};

template<auto First, auto Second, auto...Others>
struct Payroll<First, Second, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
};

template<auto First, auto Second, auto Third, auto...Others>
struct Payroll<First, Second, Third, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
};

template<auto First, auto Second, auto Third, auto Fourth, auto...Others>
struct Payroll<First, Second, Third, Fourth, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
    static constexpr auto fourth() { return Fourth; }
};
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Variables>
struct Shuttle
: public Payload<Variables...>
, public Payroll<Variables...> {};
/******************************************************************************************************/




/******************************************************************************************************/
template<size_t...Indices>
struct Shuttle<Indices...>
: public std::index_sequence<Indices...>
, public Payload<Indices...>
, public Payroll<Indices...> {};
/******************************************************************************************************/




/******************************************************************************************************/
template<size_t...Indices>
using Ark = Shuttle<Indices...>;

template<std::make_signed_t<size_t>...Indices>
using SignedArk = Shuttle<Indices...>;
/******************************************************************************************************/




}

#endif