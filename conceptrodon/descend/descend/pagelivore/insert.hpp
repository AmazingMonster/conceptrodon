// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_INSERT_H
#define CONCEPTRODON_PAGELIVORE_INSERT_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/omennivore/insert_variables.hpp"
#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/descend/pagelivore/segment.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Insert
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
        
        struct Slash
        {
            template<size_t...I>
            struct ProtoPage
            {
                template<auto...NewVariables>
                using Page = Omennivore::Send
                <
                    typename Omennivore::Send
                    <
                        typename Pagelivore::Segment<Detail_t>
                        ::template Page<I...>
                    >::template UniRoad<Omennivore::InsertVariables>
                    ::template Page<NewVariables...>
                    ::template Page_t<Variables...>
                >
                ::template UniRail<Operation>;
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif