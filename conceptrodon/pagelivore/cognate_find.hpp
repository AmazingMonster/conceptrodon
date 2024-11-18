// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_FIND_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_FIND_H

#include "conceptrodon/microbiota/varbola/find.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Predicates>
struct CognateFind
{
    template<auto...Variables>
    using Page 
    = Varbola::Find<Variables...>
    ::template ProtoRail<Predicates...>;

    template<auto...Variables>
    static constexpr auto Page_v
    {
        Varbola::Find<Variables...>
        ::template Rail_v<Predicates...>
    };
};

}}

#endif