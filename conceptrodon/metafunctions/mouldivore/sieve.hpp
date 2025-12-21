// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_SIEVE_H
#define CONCEPTRODON_MOULDIVORE_SIEVE_H

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/cotanivore/paste.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Predicates>
struct Sieve
{
    template<typename Element>
    struct Detail 
    { using type = Capsule<>; };

    template<typename Element>
    requires (not (...&&Predicates<Element>::value))
    struct Detail<Element>
    { using type = Capsule<Element>; };

    template<typename...Elements>
    using Mold = Cotanivore::TypicalPaste
    <typename Detail<Elements>::type...>::type;
};

}}

#endif