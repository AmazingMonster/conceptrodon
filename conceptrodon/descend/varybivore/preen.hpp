// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_PREEN_H
#define CONCEPTRODON_VARYBIVORE_PREEN_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Preen
{
    template<template<auto...> class Cosmetic>
    struct ProtoRail 
    { using type = Capsule<typename Cosmetic<Variables>::type...>; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<auto...> class...Args>
    using Rail_t = ProtoRail<Args...>::type;

    template<template<auto...> class Cosmetic>
    using UniRail = Capsule<typename Cosmetic<Variables>::type...>;
};

}}

#endif