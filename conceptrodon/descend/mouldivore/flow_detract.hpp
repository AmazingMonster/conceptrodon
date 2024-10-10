// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_FLOW_DETRACT_H
#define CONCEPTRODON_MOULDIVORE_FLOW_DETRACT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct FlowDetract
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Operation<Agreements...>::type>::template UniZeal<Negotiation::template Flow>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif