// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PHANTOM_H
#define CONCEPTRODON_PHANTOM_H

namespace Conceptrodon {
    
template<template<auto...> class...Sequences>
struct Phantom
{
    static constexpr size_t size() { return sizeof...(Sequences); }

    template<template<template<auto...> class...> class Stockroom>
    struct Detail { using type = Stockroom<Sequences...>; };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = Detail<Stockrooms...>::type;
    
    template<template<template<auto...> class...> class Stockroom>
    using UniSail = Stockroom<Sequences...>;
};
 
}

#endif

