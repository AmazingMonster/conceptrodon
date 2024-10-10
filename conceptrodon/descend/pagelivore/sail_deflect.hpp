// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SAIL_DEFLECT_H
#define CONCEPTRODON_PAGELIVORE_SAIL_DEFLECT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct SailDeflect
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Omennivore::Send<Operation<Agreements...>>::template UniZest<Negotiation::template Sail>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif