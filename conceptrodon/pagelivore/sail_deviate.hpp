// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SAIL_DEVIATE_H
#define CONCEPTRODON_PAGELIVORE_SAIL_DEVIATE_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct SailDeviate
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Negotiation::template Sail<Operation<Agreements...>::template Rail>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif