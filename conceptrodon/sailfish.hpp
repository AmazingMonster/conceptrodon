// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SAILFISH_H
#define CONCEPTRODON_SAILFISH_H

namespace Conceptrodon {

template<template<template<template<auto...> class...> class...> class Melancholy>
struct Sailfish
{
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = Melancholy<Stockrooms...>;
};

}

#endif