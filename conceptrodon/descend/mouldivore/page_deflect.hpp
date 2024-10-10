// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_PAGE_DEFLECT_H
#define CONCEPTRODON_MOULDIVORE_PAGE_DEFLECT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct PageDeflect
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<Operation<Agreements...>>::template UniRail<Negotiation::template Page>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif