// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_EMISSARY_H
#define CONCEPTRODON_EMISSARY_H

namespace Conceptrodon {

template<template<typename...> class Container>
struct Emissary
{
    template<typename...Elements>
    using Mold = Container<Elements...>;
};

}

#endif