// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LEGATION_H
#define CONCEPTRODON_LEGATION_H

namespace Conceptrodon {

template<template<template<auto...> class...> class Stockroom>
struct Legation
{
    template<template<auto...> class...Sequences>
    using Rail = Stockroom<Sequences...>;
};

}

#endif