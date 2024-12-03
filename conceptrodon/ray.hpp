// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAY_H
#define CONCEPTRODON_RAY_H

namespace Conceptrodon {

template<template<template<auto...> class...> class Stockroom>
struct Ray
{
    template<template<auto...> class...Sequences>
    using Rail = Stockroom<Sequences...>;
};

}

#endif