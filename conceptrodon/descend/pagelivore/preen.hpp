// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_PREEN_H
#define CONCEPTRODON_PAGELIVORE_PREEN_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Cosmetic>
struct Preen
{
    template<auto...Variables>
    struct ProtoPage 
    { using type = Capsule<typename Cosmetic<Variables>::type...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = Capsule<typename Cosmetic<Variables>::type...>;
};

}}

#endif