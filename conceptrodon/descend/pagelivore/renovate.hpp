// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RENOVATE_H
#define CONCEPTRODON_PAGELIVORE_RENOVATE_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Decorations>
struct Renovate
{
    template<auto...Variables>
    struct ProtoPage 
    { using type = Capsule<Decorations<Variables>...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = Capsule<Decorations<Variables>...>;
};

}}

#endif