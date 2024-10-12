// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_RAIL_DEVIATE_H
#define CONCEPTRODON_ROADRIVORE_RAIL_DEVIATE_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct RailDeviate
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<template<typename...> class...Agreements>
        using Road = Negotiation::template Rail<Operation<Agreements...>::template Page>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif