// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_SNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_SNOWFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsSnowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct IsSnowful<Silence<Sorrow...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsSnowful_v {false};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
constexpr bool IsSnowful_v<Silence<Sorrow...>> {true};

}}

#endif