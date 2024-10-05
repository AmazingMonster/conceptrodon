// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_PLUME_H
#define CONCEPTRODON_PAGELIVORE_PLUME_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Cosmetics>
struct Plume
{
    template<auto...Variables>
    struct ProtoPage 
    { using type = Capsule<typename Cosmetics<Variables>::type...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = Capsule<typename Cosmetics<Variables>::type...>;
};

}}

#endif