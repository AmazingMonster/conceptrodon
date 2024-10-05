// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_RAILWAY_H
#define CONCEPTRODON_OMENNIVORE_IS_RAILWAY_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsRailway
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailway<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsRailway_v {false};

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
constexpr bool IsRailway_v<Stockroom<Sequences...>> {true};

}}

#endif