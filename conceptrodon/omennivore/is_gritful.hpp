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
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines
>
struct IsGritful<Sunshine<Sunshines...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsGritful_v {false};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines
>
constexpr bool IsGritful_v<Sunshine<Sunshines...>> {true};

}}

#endif