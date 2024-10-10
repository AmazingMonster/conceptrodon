// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_MOLD_DIVERGE_H
#define CONCEPTRODON_MOULDIVORE_MOLD_DIVERGE_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct MoldDiverge
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<typename...Agreements>
        using Mold = Negotiation::template Mold<Operation<Agreements...>>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif