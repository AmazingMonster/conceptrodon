// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_DEFER_H
#define CONCEPTRODON_MOULDIVORE_DEFER_H

#include "conceptrodon/descend/mouldivore/short_defer.hpp"
#include "conceptrodon/omennivore/concepts/flow_probe.hpp"
#include "conceptrodon/omennivore/concepts/sail_probe.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Defer
{
    template<typename Negotiation>
    struct ProtoMold
    : public ShortDefer<Operation>::template ProtoMold<Negotiation> {};

    template<typename Negotiation>
    requires Omennivore::FlowProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortDefer<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<typename...> class...> class...Agreements>
        using Flow = Operation<typename Negotiation::template Flow<Agreements...>>;
    };

    template<typename Negotiation>
    requires Omennivore::SailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortDefer<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<auto...> class...> class...Agreements>
        using Sail = Operation<typename Negotiation::template Sail<Agreements...>>;
    };

    template<typename Negotiation>
    requires Omennivore::FlowProbe<Negotiation>
    && Omennivore::SailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortDefer<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<typename...> class...> class...Agreements>
        using Flow = Operation<typename Negotiation::template Flow<Agreements...>>;
        
        template<template<template<auto...> class...> class...Agreements>
        using Sail = Operation<typename Negotiation::template Sail<Agreements...>>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif