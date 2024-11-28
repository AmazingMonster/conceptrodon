// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TRAVAIL_H
#define CONCEPTRODON_TRAVAIL_H

namespace Conceptrodon {
    
template<template<template<template<auto...> class...> class...> class...Nothingness>
struct Travail 
{
    static constexpr size_t size() { return sizeof...(Nothingness); }

    template<template<template<template<template<auto...> class...> class...> class...> class Revelation>
    struct Detail { using type = Revelation<Nothingness...>; };

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = Detail<Tranquil...>::type;
    
    template<template<template<template<template<auto...> class...> class...> class...> class Revelation>
    using UniCalm = Revelation<Nothingness...>;
};
 
}

#endif