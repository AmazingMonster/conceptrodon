// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_FIND_H
#define CONCEPTRODON_PAGELIVORE_FIND_H

#include "conceptrodon/microbiota/varbola/kindred_find.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Predicates>
struct Find
{
    template<auto...Variables>
    using Page 
    = Varbola::KindredFind<Variables...>
    ::template ProtoRail<Predicates...>;

    template<auto...Variables>
    static constexpr std::make_signed_t<size_t> Page_v
    {
        Varbola::KindredFind<Variables...>
        ::template Rail_v<Predicates...>
    };
};

}}

#endif