// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_SIEVE_H
#define CONCEPTRODON_MOULDIVORE_SIEVE_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/cotanivore/paste.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct Sieve
{
    template<typename Element>
    struct Detail 
    { using type = Capsule<>; };

    template<typename Element>
    requires (not Predicate<Element>::value)
    struct Detail<Element>
    { using type = Capsule<Element>; };

    template<typename...Elements>
    struct ProtoMold
    { 
        using type = Cotanivore::Paste
        <typename Detail<Elements>::type...>::type; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = Cotanivore::Paste
    <typename Detail<Elements>::type...>::type; 
};

}}

#endif