// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_FILTER_H
#define CONCEPTRODON_PAGELIVORE_FILTER_H

#include "conceptrodon/descend/pagelivore/sieve.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation=Shuttle>
struct Filter
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Omennivore::Send<typename Sieve<Predicate>::template Page_t<Variables...>>
        ::template UniRail<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif