// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_DELEGACY_H
#define CONCEPTRODON_DELEGACY_H

namespace Conceptrodon {

template<template<template<typename...> class...> class Warehouse>
struct Delegacy
{
    template<template<typename...> class...Containers>
    using Road = Warehouse<Containers...>;
};

}

#endif