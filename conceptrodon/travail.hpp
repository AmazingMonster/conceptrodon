// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TRAVAIL_H
#define CONCEPTRODON_TRAVAIL_H

namespace Conceptrodon {
    
template<template<template<auto...> class...> class...Things>
struct Travail
{
    static constexpr size_t size() { return sizeof...(Things); }

    template<template<template<template<auto...> class...> class...> class Intoxication>
    struct Detail { using type = Intoxication<Things...>; };

    template<template<template<template<auto...> class...> class...> class...Foolishness>
    using Hail = Detail<Foolishness...>::type;

    template<template<template<template<auto...> class...> class...> class Intoxication>
    using UniHail = Intoxication<Things...>;
};
 
}

#endif