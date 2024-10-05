// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_GRADE_H
#define CONCEPTRODON_VARYBIVORE_GRADE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Grade
{
    template<template<auto...> class Paper>
    struct ProtoRail
    { using type = Shuttle<Paper<Variables>::value...>; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<auto...> class...Args>
    using Rail_t = ProtoRail<Args...>::type;

    template<template<auto...> class Paper>
    using UniRail = Shuttle<Paper<Variables>::value...>;
};

}}

#endif