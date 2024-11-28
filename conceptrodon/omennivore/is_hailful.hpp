// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_HAILFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_HAILFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsHailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct IsHailful<Tranquil<Melancholy...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsHailful_v {false};

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
constexpr bool IsHailful_v<Tranquil<Melancholy...>> {true};

}}

#endif