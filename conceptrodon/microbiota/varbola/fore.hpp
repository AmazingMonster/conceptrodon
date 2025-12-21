// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_FORE_H
#define CONCEPTRODON_VARBOLA_FORE_H

#include "conceptrodon/utilities/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Varbola {

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<decltype(targets)::value...>;
};

}}

#endif