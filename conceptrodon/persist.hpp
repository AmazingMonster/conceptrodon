// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PERSIST_H
#define CONCEPTRODON_PERSIST_H

namespace Conceptrodon {
    
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines>
struct Persist 
{
    static constexpr size_t size() { return sizeof...(Sunshines); }

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Beginning>
    struct Detail { using type = Beginning<Sunshines...>; };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = Detail<Agreements...>::type;
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Beginning>
    using UniDawn = Beginning<Sunshines...>;
};
 
}

#endif