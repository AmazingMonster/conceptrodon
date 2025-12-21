// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_FIND_H
#define CONCEPTRODON_MOULDIVORE_FIND_H

#include "conceptrodon/metafunctions/microbiota/typella/kindred_find.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct Find
{
    template<typename...Elements>
    using Mold = Typella::KindredFind<Elements...>
    ::template ProtoRoad<Predicate>;

    template<typename...Elements>
    static constexpr auto Mold_v
    {
        Typella::KindredFind<Elements...>
        ::template Road_v<Predicate>
    };
};

}}

#endif