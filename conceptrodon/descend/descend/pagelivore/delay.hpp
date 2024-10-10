// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_DELAY_H
#define CONCEPTRODON_PAGELIVORE_DELAY_H

#include "conceptrodon/descend/pagelivore/short_delay.hpp"
#include "conceptrodon/omennivore/concepts/flow_probe.hpp"
#include "conceptrodon/omennivore/concepts/sail_probe.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Delay
{
    template<typename Negotiation>
    struct ProtoMold
    : public ShortDelay<Operation>::template ProtoMold<Negotiation> {};

    template<typename Negotiation>
    requires Omennivore::FlowProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortDelay<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<typename...> class...> class...Agreements>
        using Flow = Operation<Negotiation::template Flow<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::SailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortDelay<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<auto...> class...> class...Agreements>
        using Sail = Operation<Negotiation::template Sail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::FlowProbe<Negotiation>
    && Omennivore::SailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortDelay<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<typename...> class...> class...Agreements>
        using Flow = Operation<Negotiation::template Flow<Agreements...>::value>;
        
        template<template<template<auto...> class...> class...Agreements>
        using Sail = Operation<Negotiation::template Sail<Agreements...>::value>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif