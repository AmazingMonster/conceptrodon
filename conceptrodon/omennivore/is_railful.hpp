// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_RAILFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_RAILFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsRailful_v {false};

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
constexpr bool IsRailful_v<Stockroom<Sequences...>> {true};

}}

#endif