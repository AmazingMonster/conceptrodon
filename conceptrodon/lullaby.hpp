// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LULLABY_H
#define CONCEPTRODON_LULLABY_H

namespace Conceptrodon {
    
template<template<template<template<typename...> class...> class...> class...Nothingness>
struct Lullaby 
{
    static constexpr size_t size() { return sizeof...(Nothingness); }

    template<template<template<template<template<typename...> class...> class...> class...> class Revelation>
    struct Detail { using type = Revelation<Nothingness...>; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Lull = Detail<Silence...>::type;
    
    template<template<template<template<template<typename...> class...> class...> class...> class Revelation>
    using UniLull = Revelation<Nothingness...>;
};
 
}

#endif