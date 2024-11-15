// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_PAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_PAGEFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsPageful
{ static constexpr bool value {false}; };

template<template<auto...> class Sequence, auto...Variables>
struct IsPageful<Sequence<Variables...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsPageful_v {false};

template<template<auto...> class Sequence, auto...Variables>
constexpr bool IsPageful_v<Sequence<Variables...>> {true};

}}

#endif