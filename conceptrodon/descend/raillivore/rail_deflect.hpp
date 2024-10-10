// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_RAIL_DEFLECT_H
#define CONCEPTRODON_RAILLIVORE_RAIL_DEFLECT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct RailDeflect
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<Operation<Agreements...>>::template UniSail<Negotiation::template Rail>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif