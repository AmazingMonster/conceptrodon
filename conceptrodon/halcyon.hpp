// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_HALCYON_H
#define CONCEPTRODON_HALCYON_H

namespace Conceptrodon {
    
template<template<template<template<template<auto...> class...> class...> class...> class...Dreams>
struct Halcyon 
{
    static constexpr size_t size() { return sizeof...(Dreams); }

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Realization>
    struct Detail { using type = Realization<Dreams...>; };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = Detail<Agreements...>::type;
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Realization>
    using UniWill = Realization<Dreams...>;
};
 
}

#endif