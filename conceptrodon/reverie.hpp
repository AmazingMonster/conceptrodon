// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_REVERIE_H
#define CONCEPTRODON_REVERIE_H

namespace Conceptrodon {
    
template<template<template<typename...> class...> class...Things>
struct Reverie
{
    static constexpr size_t size() { return sizeof...(Things); }

    template<template<template<template<typename...> class...> class...> class Intoxication>
    struct Detail { using type = Intoxication<Things...>; };

    template<template<template<template<typename...> class...> class...> class...Foolishness>
    using Snow = Detail<Foolishness...>::type;
    
    template<template<template<template<typename...> class...> class...> class Intoxication>
    using UniSnow = Intoxication<Things...>;
};
 
}

#endif