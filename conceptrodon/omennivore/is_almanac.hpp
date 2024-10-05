// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_ALMANAC_H
#define CONCEPTRODON_OMENNIVORE_IS_ALMANAC_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsAlmanac
{ static constexpr bool value {false}; };

template<template<auto...> class Sequence, auto...Variables>
struct IsAlmanac<Sequence<Variables...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsAlmanac_v {false};

template<template<auto...> class Sequence, auto...Variables>
constexpr bool IsAlmanac_v<Sequence<Variables...>> {true};

}}

#endif