// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_FILTER_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_FILTER_H

#include "conceptrodon/metafunctions/pagelivore/sieve.hpp"
#include "conceptrodon/metafunctions/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateFilter
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Omennivore::Send
        <
            typename Sieve<Predicates...>
            ::template Page<Variables...>
        >
        ::template UniRail<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif