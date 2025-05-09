// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PURSUIT_H
#define CONCEPTRODON_PURSUIT_H

namespace Conceptrodon {
    
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
struct Pursuit 
{
    static constexpr size_t size() { return sizeof...(Consistency); }

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Beginning>
    struct Detail { using type = Beginning<Consistency...>; };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = Detail<Agreements...>::type;
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Beginning>
    using UniGlow = Beginning<Consistency...>;
};
 
}

#endif