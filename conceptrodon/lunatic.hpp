// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LUNATIC_H
#define CONCEPTRODON_LUNATIC_H

namespace Conceptrodon {
    
template<template<template<auto...> class...> class...Things>
struct Lunatic
{
    static constexpr size_t size() { return sizeof...(Things); }

    template<template<template<template<auto...> class...> class...> class Intoxication>
    struct Detail { using type = Intoxication<Things...>; };

    template<template<template<template<auto...> class...> class...> class...Craziness>
    using Zest = Detail<Craziness...>::type;

    template<template<template<template<auto...> class...> class...> class Intoxication>
    using UniZest = Intoxication<Things...>;
};
 
}

#endif