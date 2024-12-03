// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOY_H
#define CONCEPTRODON_MOY_H

namespace Conceptrodon {

template<template<typename...> class Container>
struct Moy
{
    template<typename...Elements>
    using Mold = Container<Elements...>;
};

}

#endif