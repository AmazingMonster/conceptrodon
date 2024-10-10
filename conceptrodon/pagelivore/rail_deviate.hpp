// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RAIL_DEVIATE_H
#define CONCEPTRODON_PAGELIVORE_RAIL_DEVIATE_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct RailDeviate
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Negotiation::template Rail<Operation<Agreements...>::template Page>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif