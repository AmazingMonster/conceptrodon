// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UPEND_H
#define CONCEPTRODON_VARYBIVORE_UPEND_H

#include "conceptrodon/descend/stamp.hpp"
#include <utility>

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Upend
{
    template<template<auto...> class, typename>
    struct Detail {};

    template<template<auto...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    : public Stamp<Variables, I>...
    {
        using Stamp<Variables, I>::idyl...;
        using type = Operation
        <
            decltype
            (
                idyl(std::integral_constant<size_t, sizeof...(I) - I - 1>{})
            )::value...
        >;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements..., std::make_index_sequence<sizeof...(Variables)>>::type;
};

}}

#endif