// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_RAIL_DEVIATE_H
#define CONCEPTRODON_RAILLIVORE_RAIL_DEVIATE_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct RailDeviate
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<template<auto...> class...Agreements>
        using Rail = Negotiation::template Rail<Operation<Agreements...>::template Page>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif