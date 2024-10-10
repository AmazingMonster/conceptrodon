// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LULLABY_H
#define CONCEPTRODON_LULLABY_H

namespace Conceptrodon {
    
template<template<template<template<typename...> class...> class...> class...Nothing>
struct Lullaby 
{
    static constexpr size_t size() { return sizeof...(Nothing); }

    template<template<template<template<template<typename...> class...> class...> class...> class Revelation>
    struct Detail { using type = Revelation<Nothing...>; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Lull = Detail<Silence...>::type;
    
    template<template<template<template<template<typename...> class...> class...> class...> class Revelation>
    using UniLull = Revelation<Nothing...>;
};
 
}

#endif