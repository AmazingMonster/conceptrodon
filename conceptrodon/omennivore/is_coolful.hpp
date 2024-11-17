// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_COOLFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsCoolful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct IsCoolful<Sunshine<Silence...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsCoolful_v {false};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
constexpr bool IsCoolful_v<Sunshine<Silence...>> {true};

}}

#endif