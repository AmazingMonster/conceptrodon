// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_REMOVE_H
#define CONCEPTRODON_PAGELIVORE_REMOVE_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/omennivore/remove_values.hpp"
#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/descend/pagelivore/segment.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Remove
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
                typename Pagelivore::Segment<Detail_t>
                ::template Page<I...>
            >::template UniRoad<Omennivore::RemoveValues>
            ::template Page_t<Variables...>
        >
        ::template UniRail<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif