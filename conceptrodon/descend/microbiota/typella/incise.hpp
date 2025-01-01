// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_INCISE_H
#define CONCEPTRODON_TYPELLA_INCISE_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {

namespace Typella {

template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Prefix<J> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};

}}

#endif