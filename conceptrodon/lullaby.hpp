// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LULLABY_H
#define CONCEPTRODON_LULLABY_H

#include <cstddef>

namespace Conceptrodon {
    
template<template<template<template<template<typename...> class...> class...> class...> class...Dreams>
struct Lullaby 
{
    static constexpr size_t size() { return sizeof...(Dreams); }

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Realization>
    struct Detail { using type = Realization<Dreams...>; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = Detail<Agreements...>::type;
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Realization>
    using UniGrit = Realization<Dreams...>;
};
 
}

#endif