// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_SHORT_PAUSE_H
#define CONCEPTRODON_ROADRIVORE_SHORT_PAUSE_H

#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/omennivore/concepts/mold_probe.hpp"
#include "conceptrodon/omennivore/concepts/page_probe.hpp"
#include "conceptrodon/omennivore/concepts/road_probe.hpp"
#include "conceptrodon/omennivore/concepts/rail_probe.hpp"

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct ShortPause
{
    template<typename Negotiation>
    struct ProtoMold {};

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;

        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;

        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;

        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;

        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;

        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;

        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;

        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;

        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;

        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;

        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;

        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;

        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;

        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;

        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename Negotiation>
    requires Omennivore::MoldProbe<Negotiation>
    && Omennivore::PageProbe<Negotiation>
    && Omennivore::RoadProbe<Negotiation>
    && Omennivore::RailProbe<Negotiation>
    struct ProtoMold<Negotiation>
    {
        template<typename...Agreements>
        using Mold = Omennivore::Send<typename Negotiation::template Mold<Agreements...>::type>::template UniFlow<Operation>;

        template<auto...Agreements>
        using Page = Omennivore::Send<typename Negotiation::template Page<Agreements...>::type>::template UniFlow<Operation>;

        template<template<typename...> class...Agreements>
        using Road = Omennivore::Send<typename Negotiation::template Road<Agreements...>::type>::template UniFlow<Operation>;

        template<template<auto...> class...Agreements>
        using Rail = Omennivore::Send<typename Negotiation::template Rail<Agreements...>::type>::template UniFlow<Operation>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif