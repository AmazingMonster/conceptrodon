// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_GRADE_H
#define CONCEPTRODON_PAGELIVORE_GRADE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Paper>
struct Grade
{
    template<auto...Variables>
    struct ProtoPage 
    { using type = Shuttle<Paper<Variables>::value...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = Shuttle<Paper<Variables>::value...>;
};

}}

#endif