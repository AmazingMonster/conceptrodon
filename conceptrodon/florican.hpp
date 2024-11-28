// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FLORICAN_H
#define CONCEPTRODON_FLORICAN_H

namespace Conceptrodon {

template<template<template<template<typename...> class...> class...> class Sorrow>
struct Florican
{
    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Sorrow<Warehouses...>;
};

}

#endif