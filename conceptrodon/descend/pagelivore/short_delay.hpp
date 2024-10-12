// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SHORT_DELAY_H
#define CONCEPTRODON_PAGELIVORE_SHORT_DELAY_H

#include "conceptrodon/omennivore/concepts/mold_probe.hpp"
#include "conceptrodon/omennivore/concepts/page_probe.hpp"
#include "conceptrodon/omennivore/concepts/road_probe.hpp"
#include "conceptrodon/omennivore/concepts/rail_probe.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct ShortDelay
{
    template<typename Negotiation>
    struct ProtoMold {};

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;

        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;

        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;

        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;

        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;

        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;

        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;

        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;

        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;

        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;

        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;

        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;

        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;

        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;

        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Operation<Negotiation::template Mold<Agreements...>::value>;

        template<auto...Agreements>
        using Page = Operation<Negotiation::template Page<Agreements...>::value>;

        template<template<typename...> class...Agreements>
        using Road = Operation<Negotiation::template Road<Agreements...>::value>;

        template<template<auto...> class...Agreements>
        using Rail = Operation<Negotiation::template Rail<Agreements...>::value>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif