// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_DAWNFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_DAWNFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsDawnful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsDawnful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsDawnful_v {false};

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
constexpr bool IsDawnful_v<Sunlight<Sunshines...>> {true};

}}

#endif