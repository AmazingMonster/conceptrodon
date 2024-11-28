// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_HALFMOON_H
#define CONCEPTRODON_HALFMOON_H

namespace Conceptrodon {

template<template<template<template<template<auto...> class...> class...> class...> class Tranquil>
struct Halfmoon
{
    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = Tranquil<Melancholy...>;
};

}

#endif