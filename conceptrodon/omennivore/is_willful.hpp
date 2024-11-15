// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_WILLFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_WILLFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsWillful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines
>
struct IsWillful<Sunshine<Sunshines...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsWillful_v {false};

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines
>
constexpr bool IsWillful_v<Sunshine<Sunshines...>> {true};

}}

#endif