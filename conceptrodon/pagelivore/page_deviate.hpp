// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_PAGE_DEVIATE_H
#define CONCEPTRODON_PAGELIVORE_PAGE_DEVIATE_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct PageDeviate
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Negotiation::template Page<Operation<Agreements...>::value>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif