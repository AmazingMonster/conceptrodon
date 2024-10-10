// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_PAGE_DEFLECT_H
#define CONCEPTRODON_ROADRIVORE_PAGE_DEFLECT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct PageDeflect
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<Operation<Agreements...>>::template UniRail<Negotiation::template Page>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif