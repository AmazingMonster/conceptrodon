// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_PAUSE_H
#define CONCEPTRODON_MOULDIVORE_PAUSE_H

#include "conceptrodon/descend/mouldivore/short_pause.hpp"
#include "conceptrodon/omennivore/concepts/flow_probe.hpp"
#include "conceptrodon/omennivore/concepts/sail_probe.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Pause
{
    template<typename Negotiation>
    struct ProtoMold
    : public ShortPause<Operation>::template ProtoMold<Negotiation> {};

    template<typename Negotiation>
    requires Omennivore::FlowProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortPause<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<typename...> class...> class...Agreements>
        using Flow = Omennivore::Send<typename Negotiation::template Flow<Agreements...>::type>::template UniRoad<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::SailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortPause<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<auto...> class...> class...Agreements>
        using Sail = Omennivore::Send<typename Negotiation::template Sail<Agreements...>::type>::template UniRoad<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::FlowProbe<Negotiation>
    && Omennivore::SailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    : public ShortPause<Operation>::template ProtoMold<Negotiation>
    {
        template<template<template<typename...> class...> class...Agreements>
        using Flow = Omennivore::Send<typename Negotiation::template Flow<Agreements...>::type>::template UniRoad<Operation>;
        
        template<template<template<auto...> class...> class...Agreements>
        using Sail = Omennivore::Send<typename Negotiation::template Sail<Agreements...>::type>::template UniRoad<Operation>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif