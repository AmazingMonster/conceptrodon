// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_RISE_H
#define CONCEPTRODON_VARBOLA_RISE_H

#include <algorithm>
#include <type_traits>
#include <utility>
#include <array>

namespace Conceptrodon {
namespace Varbola {

template<template<auto...> class Operation, auto...Variables>
static consteval auto arise()
{
    return []<size_t...I>(std::index_sequence<I...>)
    {
        constexpr auto sorted = []()
        {
            std::array original {Variables...};
            std::ranges::sort(original);
            return original;
        }();
        return std::type_identity<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};

}}

#endif