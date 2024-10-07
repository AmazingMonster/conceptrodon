// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FOOLERY_H
#define CONCEPTRODON_FOOLERY_H

namespace Conceptrodon {
    
template<template<template<typename...> class...> class...Things>
struct Foolery
{
    static constexpr size_t size() { return sizeof...(Things); }

    template<template<template<template<typename...> class...> class...> class Intoxication>
    struct Detail { using type = Intoxication<Things...>; };

    template<template<template<template<typename...> class...> class...> class...Madness>
    using Zeal = Detail<Madness...>::type;
    
    template<template<template<template<typename...> class...> class...> class Intoxication>
    using UniZeal = Intoxication<Things...>;
};
 
}

#endif