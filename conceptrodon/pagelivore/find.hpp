// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_FIND_H
#define CONCEPTRODON_PAGELIVORE_FIND_H

#include "conceptrodon/microbiota/varbola/find.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct Find
{
    template<auto...Variables>
    using Page 
    = Varbola::Find<Variables...>
    ::template ProtoRail<Predicate>;

    template<auto...Variables>
    static constexpr auto Page_v
    {
        Varbola::Find<Variables...>
        ::template Rail_v<Predicate>
    };
};

}}

#endif