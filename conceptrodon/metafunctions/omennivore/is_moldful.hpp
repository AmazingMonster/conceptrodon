// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_MOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_MOLDFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsMoldful_v {false};

template<template<typename...> class Container, typename...Elements>
constexpr bool IsMoldful_v<Container<Elements...>> {true};

}}

#endif