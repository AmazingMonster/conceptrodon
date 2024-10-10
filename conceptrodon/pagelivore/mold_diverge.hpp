// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_MOLD_DIVERGE_H
#define CONCEPTRODON_PAGELIVORE_MOLD_DIVERGE_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct MoldDiverge
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Negotiation::template Mold<Operation<Agreements...>>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif