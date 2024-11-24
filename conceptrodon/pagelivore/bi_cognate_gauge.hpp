// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_BI_COGNATE_GAUGE_H
#define CONCEPTRODON_PAGELIVORE_BI_COGNATE_GAUGE_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct BiCognateGauge
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Devices<Variables>::value...>;
        };

        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<Devices<Variable>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class Device>
    struct ProtoRail<Device>
    {
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Device<Variables>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<typename...> class...Devices>
    struct ProtoRoad
    {
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Devices<Elements>::value...>;
        };

        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    {
        template<typename...Variables>
        struct Detail
        {
            using type = Operation<Device<Variables>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif