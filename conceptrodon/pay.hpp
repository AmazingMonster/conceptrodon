// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAY_H
#define CONCEPTRODON_PAY_H

namespace Conceptrodon {

template<template<auto...> class Sequence>
struct Pay
{
    template<auto...Variables>
    using Page = Sequence<Variables...>;
};

}

#endif