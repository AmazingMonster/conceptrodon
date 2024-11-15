// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_SAILFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_SAILFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsSailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...Stockrooms
>
struct IsSailful<Melancholy<Stockrooms...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsSailful_v {false};

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...Stockrooms
>
constexpr bool IsSailful_v<Melancholy<Stockrooms...>> {true};

}}

#endif