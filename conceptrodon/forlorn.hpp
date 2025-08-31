// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FORLORN_H
#define CONCEPTRODON_FORLORN_H

#include <cstddef>

namespace Conceptrodon {
    
template<template<template<template<typename...> class...> class...> class...Nothingness>
struct Forlorn 
{
    static constexpr size_t size() { return sizeof...(Nothingness); }

    template<template<template<template<template<typename...> class...> class...> class...> class Revelation>
    struct Detail { using type = Revelation<Nothingness...>; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = Detail<Silence...>::type;
    
    template<template<template<template<template<typename...> class...> class...> class...> class Revelation>
    using UniCool = Revelation<Nothingness...>;
};
 
}

#endif