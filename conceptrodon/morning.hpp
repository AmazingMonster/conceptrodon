// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MORNING_H
#define CONCEPTRODON_MORNING_H

namespace Conceptrodon {
    
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines>
struct Morning 
{
    static constexpr size_t size() { return sizeof...(Sunshines); }

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Beginning>
    struct Detail { using type = Beginning<Sunshines...>; };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = Detail<Agreements...>::type;
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Beginning>
    using UniGlow = Beginning<Sunshines...>;
};
 
}

#endif