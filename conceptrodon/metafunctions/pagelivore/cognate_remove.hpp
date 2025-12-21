// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_REMOVE_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_REMOVE_H

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/omennivore/remove_values.hpp"
#include "conceptrodon/metafunctions/omennivore/send.hpp"
#include "conceptrodon/metafunctions/pagelivore/cognate_segment.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateRemove
{
    template<size_t I, size_t...J>
    using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

    template<size_t...I>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Omennivore::Send
        <
            typename Omennivore::Send
            <
                typename CognateSegment<Detail_t>
                ::template Page<I...>
            >::template UniRoad<Omennivore::RemoveValues>
            ::template Page<Variables...>
        >
        ::template UniRail<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif