// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_REPEAT_H
#define CONCEPTRODON_PAGELIVORE_REPEAT_H

#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/descend/microbiota/varbola/reiterate.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Repeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Omennivore::Send
        <
            typename Varbola::Reiterate<Variables...>
            ::template ProtoPage<Amount>::type
        >
        ::template UniRail<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif