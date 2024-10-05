// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_REFURBISH_H
#define CONCEPTRODON_PAGELIVORE_REFURBISH_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Decoration>
struct Refurbish
{
    template<auto...Variables>
    struct ProtoPage 
    { using type = Capsule<Decoration<Variables>...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = Capsule<Decoration<Variables>...>;
};

}}

#endif