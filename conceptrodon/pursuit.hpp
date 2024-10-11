// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PURSUIT_H
#define CONCEPTRODON_PURSUIT_H

namespace Conceptrodon {
    
template<template<template<template<template<typename...> class...> class...> class...> class...Dreams>
struct Pursuit 
{
    static constexpr size_t size() { return sizeof...(Dreams); }

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Realization>
    struct Detail { using type = Realization<Dreams...>; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Hope = Detail<Agreements...>::type;
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Realization>
    using UniHope = Realization<Dreams...>;
};
 
}

#endif