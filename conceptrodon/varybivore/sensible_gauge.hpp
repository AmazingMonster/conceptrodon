// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SENSIBLE_GAUGE_H
#define CONCEPTRODON_VARYBIVORE_SENSIBLE_GAUGE_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<auto...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Variables>::value...>;
        };
        
        template<template<auto...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Variables>::value...>;
        };

        template<template<auto...> class...Devices>
        using Rail = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto Variable>
struct SensibleGauge<Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<auto...> class...Devices>
        using Rail = Operation
        <Devices<Variable>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif