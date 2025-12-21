// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_GAUGE_H
#define CONCEPTRODON_VARYBIVORE_GAUGE_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Gauge
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation<Devices<Variables>::value...>;
    };
    
    template<template<auto...> class Device>
    struct ProtoRail<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation<Device<Variables>::value...>;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};

template<auto Variable>
struct Gauge<Variable>
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variable>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation<Devices<Variable>::value...>;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};

}}

#endif