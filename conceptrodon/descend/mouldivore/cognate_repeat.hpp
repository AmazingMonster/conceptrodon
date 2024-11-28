// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_REPEAT_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_REPEAT_H

#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/descend/microbiota/typella/typical_reiterate.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Omennivore::Send
        <
            typename Typella::TypicalReiterate<Elements...>
            ::template ProtoPage<Amount>::type
        >
        ::template UniRoad<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif