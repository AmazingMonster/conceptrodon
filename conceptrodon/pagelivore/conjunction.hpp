// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_CONJUNCTION_H
#define CONCEPTRODON_PAGELIVORE_CONJUNCTION_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Predicates>
struct Conjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {(...&&Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    static constexpr bool Page_v
    {(...&&Predicates<Variables...>::value)};
};

}}

#endif