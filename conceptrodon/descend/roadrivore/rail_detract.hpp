// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_RAIL_DETRACT_H
#define CONCEPTRODON_ROADRIVORE_RAIL_DETRACT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct RailDetract
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Operation<Agreements...>::type>::template UniSail<Negotiation::template Rail>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif