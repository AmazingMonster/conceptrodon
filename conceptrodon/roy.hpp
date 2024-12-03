// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROY_H
#define CONCEPTRODON_ROY_H

namespace Conceptrodon {

template<template<template<typename...> class...> class Warehouse>
struct Roy
{
    template<template<typename...> class...Containers>
    using Road = Warehouse<Containers...>;
};

}

#endif