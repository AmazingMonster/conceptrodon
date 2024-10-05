// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_POTTERY_H
#define CONCEPTRODON_OMENNIVORE_IS_POTTERY_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsPottery
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsPottery<Container<Elements...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsPottery_v {false};

template<template<typename...> class Container, typename...Elements>
constexpr bool IsPottery_v<Container<Elements...>> {true};

}}

#endif