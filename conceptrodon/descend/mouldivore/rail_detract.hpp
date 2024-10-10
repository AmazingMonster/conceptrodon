// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_RAIL_DETRACT_H
#define CONCEPTRODON_MOULDIVORE_RAIL_DETRACT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct RailDetract
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Operation<Agreements...>::type>::template UniSail<Negotiation::template Rail>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif