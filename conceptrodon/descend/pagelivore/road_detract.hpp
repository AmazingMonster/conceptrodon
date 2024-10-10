// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_ROAD_DETRACT_H
#define CONCEPTRODON_PAGELIVORE_ROAD_DETRACT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct RoadDetract
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Omennivore::Send<typename Operation<Agreements...>::type>::template UniFlow<Negotiation::template Road>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif