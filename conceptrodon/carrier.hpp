// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CARRIER_H
#define CONCEPTRODON_CARRIER_H

namespace Conceptrodon {
    
template<template<auto...> class...Sequences>
struct Carrier
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

