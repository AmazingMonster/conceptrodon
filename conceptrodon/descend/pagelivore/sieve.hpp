// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SIEVE_H
#define CONCEPTRODON_PAGELIVORE_SIEVE_H

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/sequnivore/paste.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct Sieve
{
    template<auto Variable>
    struct Detail 
    { using type = Shuttle<>; };

    template<auto Variable>
    requires (not Predicate<Variable>::value)
    struct Detail<Variable>
    { using type = Shuttle<Variable>; };

    template<auto...Variables>
    struct ProtoPage
    { 
        using type = Sequnivore::TypicalPaste
        <typename Detail<Variables>::type...>::type; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = Sequnivore::Paste
    <typename Detail<Variables>::type...>::type; 
};

}}

#endif