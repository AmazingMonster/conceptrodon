// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SEGMENT_H
#define CONCEPTRODON_PAGELIVORE_SEGMENT_H

#include <utility>
#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/descend/microbiota/varbola/typical_pop.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Segment
{
    template<size_t I, size_t...J>
    struct Detail
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Hidden_t = Operation<I, J-K...>;
    };

    template<auto...Agreements>
    using Page = Omennivore::Send<typename Varbola::TypicalPop<Agreements...>::type>
    ::template UniRail<Detail<Agreements...>::template Hidden_t>;

    template<typename>
    struct Hidden {};

    template<size_t I, size_t...J>
    struct Hidden<std::index_sequence<I, J...>>
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Detail_t = Operation<I, J-K...>;

        using type = Omennivore::Send<typename Varbola::TypicalPop<I, J...>::type>
        ::template UniRail<Detail_t>;
    };

    template<typename...Agreements>
    using Mold = Hidden<Agreements...>::type;
};

}}

#endif