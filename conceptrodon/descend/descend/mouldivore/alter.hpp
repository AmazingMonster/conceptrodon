// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ALTER_H
#define CONCEPTRODON_MOULDIVORE_ALTER_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/omennivore/alter_types.hpp"
#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/descend/pagelivore/segment.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Alter
{
    template<template<typename...> class Hormone>
    struct ProtoRoad
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
                    typename Pagelivore::Segment<Detail_t>
                    ::template Page<I...>
                >::template UniRoad<Omennivore::AlterTypes>
                ::template ProtoRoad<Hormone>
                ::template Mold_t<Elements...>
            >
            ::template UniRoad<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif