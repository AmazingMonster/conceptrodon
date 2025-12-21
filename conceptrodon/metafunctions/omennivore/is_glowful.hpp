// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_GLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_GLOWFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsGlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsGlowful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsGlowful_v {false};

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
constexpr bool IsGlowful_v<Sunlight<Sunshines...>> {true};

}}

#endif