// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_MODIFY_H
#define CONCEPTRODON_PAGELIVORE_MODIFY_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/omennivore/modify_variables.hpp"
#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/descend/pagelivore/segment.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Modify
{
    template<template<auto...> class Hormone>
    struct ProtoRail
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
                >::template UniRoad<Omennivore::ModifyVariables>
                ::template ProtoRail<Hormone>
                ::template Page_t<Variables...>
            >
            ::template UniRail<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif