// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_CALMFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_CALMFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsCalmful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct IsCalmful<Perseverance<Tranquil...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsCalmful_v {false};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
constexpr bool IsCalmful_v<Perseverance<Tranquil...>> {true};

}}

#endif