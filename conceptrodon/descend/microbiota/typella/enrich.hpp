// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_ENRICH_H
#define CONCEPTRODON_TYPELLA_ENRICH_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template<template<typename...> class Operation, Prefix<I>...FrontTargets, typename...BackTargets>
        static consteval auto idyl() -> Operation<FrontTargets..., NewElements..., BackTargets...>;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};

}}

#endif