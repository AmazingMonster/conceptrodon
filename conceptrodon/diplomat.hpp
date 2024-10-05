// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_DIPLOMAT_H
#define CONCEPTRODON_DIPLOMAT_H

namespace Conceptrodon {

template<template<auto...> class Sequence>
struct Diplomat
{
    template<auto...Variables>
    using Page = Sequence<Variables...>;
};

}

#endif