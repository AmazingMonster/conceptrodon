// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_FORE_H
#define CONCEPTRODON_TYPELLA_FORE_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};

}}

#endif