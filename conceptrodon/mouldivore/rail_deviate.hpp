// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_RAIL_DEVIATE_H
#define CONCEPTRODON_MOULDIVORE_RAIL_DEVIATE_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct RailDeviate
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<typename...Agreements>
        using Mold = Negotiation::template Rail<Operation<Agreements...>::template Page>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif