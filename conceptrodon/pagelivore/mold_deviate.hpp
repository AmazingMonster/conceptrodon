// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_MOLD_DEVIATE_H
#define CONCEPTRODON_PAGELIVORE_MOLD_DEVIATE_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct MoldDeviate
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Negotiation::template Mold<typename Operation<Agreements...>::type>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif