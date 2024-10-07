// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_TALE_H
#define CONCEPTRODON_PAGELIVORE_TALE_H

#include "conceptrodon/omennivore/concepts/mold_probe.hpp"
#include "conceptrodon/omennivore/concepts/page_probe.hpp"
#include "conceptrodon/omennivore/concepts/road_probe.hpp"
#include "conceptrodon/omennivore/concepts/rail_probe.hpp"
#include "conceptrodon/omennivore/concepts/flow_probe.hpp"
#include "conceptrodon/omennivore/concepts/sail_probe.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Radio>
struct Tale
{
    template<auto...Songs>
    struct Detail
    {
        template<template<template<typename...> class...> class Stop>
        struct ProtoFlow {};

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
        };

        template<template<template<typename...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Mold>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Mold>>
        struct ProtoFlow<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Mold>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Mold>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Mold>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Mold>::template Sail<Stockrooms...>;
        };

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = ProtoFlow<Warehouses...>;
    };

    template<auto...Songs>
    struct Hidden
    {
        template<template<template<auto...> class...> class Stop>
        struct ProtoSail {};

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;
        };

        template<template<template<auto...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Page>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Page>>
        struct ProtoSail<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Page>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Page>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Page>::template Flow<Warehouses...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Page>::template Sail<Stockrooms...>;
        };

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = ProtoSail<Stockrooms...>;
    };

    template<auto...Songs>
    struct Secret
    {
        template<template<template<template<typename...> class...> class...> class Stop>
        struct ProtoZeal {};

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;
        };

        template<template<template<template<typename...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Road>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Road>>
        struct ProtoZeal<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Road>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Road>::template Rail<Sequences...>;

            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Road>::template Flow<Warehouses...>;

            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Road>::template Sail<Stockrooms...>;
        };

        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = ProtoZeal<Madness...>;
    };

    template<auto...Songs>
    struct Covert
    {
        template<template<template<template<auto...> class...> class...> class Stop>
        struct ProtoZest {};

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;
            
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
            
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
            
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;
            
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
            
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
        };

        template<template<template<template<auto...> class...> class...> class Stop>
        requires Omennivore::RoadProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::RailProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::FlowProbe<Stop<Radio<Songs...>::template Rail>>
        && Omennivore::SailProbe<Stop<Radio<Songs...>::template Rail>>
        struct ProtoZest<Stop>
        {
            template<template<typename...> class...Containers>
            using Road = Stop<Radio<Songs...>::template Rail>::template Road<Containers...>;

            template<template<auto...> class...Sequences>
            using Rail = Stop<Radio<Songs...>::template Rail>::template Rail<Sequences...>;
            
            template<template<template<typename...> class...> class...Warehouses>
            using Flow = Stop<Radio<Songs...>::template Rail>::template Flow<Warehouses...>;
            
            template<template<template<auto...> class...> class...Stockrooms>
            using Sail = Stop<Radio<Songs...>::template Rail>::template Sail<Stockrooms...>;
        };

        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = ProtoZest<Craziness...>;
    };
    
    template<auto...Songs>
    struct ProtoPage
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::PageProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Hidden<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::RoadProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Secret<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    && Omennivore::PageProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>,
        public Hidden<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    && Omennivore::RoadProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>,
        public Secret<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    && Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>,
        public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::PageProbe<Radio<Songs...>>
    && Omennivore::RoadProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Hidden<Songs...>,
        public Secret<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::PageProbe<Radio<Songs...>>
    && Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Hidden<Songs...>,
        public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::RoadProbe<Radio<Songs...>>
    && Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Secret<Songs...>,
        public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    && Omennivore::RoadProbe<Radio<Songs...>>
    && Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>,
        public Secret<Songs...>,
        public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    && Omennivore::PageProbe<Radio<Songs...>>
    && Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>,
        public Hidden<Songs...>,
        public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    && Omennivore::PageProbe<Radio<Songs...>>
    && Omennivore::RoadProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>,
        public Hidden<Songs...>,
        public Secret<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::PageProbe<Radio<Songs...>>
    && Omennivore::RoadProbe<Radio<Songs...>>
    && Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Hidden<Songs...>,
        public Secret<Songs...>,
        public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    requires Omennivore::MoldProbe<Radio<Songs...>>
    && Omennivore::PageProbe<Radio<Songs...>>
    && Omennivore::RoadProbe<Radio<Songs...>>
    && Omennivore::RailProbe<Radio<Songs...>>
    struct ProtoPage<Songs...>
    :   public Detail<Songs...>,
        public Hidden<Songs...>,
        public Secret<Songs...>,
        public Covert<Songs...>
    { using type = Radio<Songs...>; };

    template<auto...Songs>
    using Page = ProtoPage<Songs...>;


    template<template<template<auto...> class...> class Stop>
    struct ProtoSail
    {
        template<template<typename...> class...Containers>
        using Road = Stop<ProtoPage>::template Road<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Stop<ProtoPage>::template Rail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Stop<ProtoPage>::template Flow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Stop<ProtoPage>::template Sail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif