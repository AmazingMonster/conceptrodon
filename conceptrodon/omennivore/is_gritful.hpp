// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_GRITFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_GRITFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsGritful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
struct IsGritful<Sunshine<Consistency...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsGritful_v {false};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
constexpr bool IsGritful_v<Sunshine<Consistency...>> {true};

}}

#endif