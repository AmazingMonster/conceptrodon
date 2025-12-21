// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_REMOVE_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_REMOVE_H

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/omennivore/remove_types.hpp"
#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/pagelivore/cognate_segment.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateRemove
{
    template<size_t I, size_t...J>
    using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

    template<size_t...I>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Omennivore::Send
        <
            typename Omennivore::Send
            <
                typename Pagelivore::CognateSegment<Detail_t>
                ::template Page<I...>
            >::template UniRoad<Omennivore::RemoveTypes>
            ::template Mold<Elements...>
        >
        ::template UniRoad<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif