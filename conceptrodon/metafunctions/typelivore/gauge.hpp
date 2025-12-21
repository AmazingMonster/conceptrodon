// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_GAUGE_H
#define CONCEPTRODON_TYPELIVORE_GAUGE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Gauge
{
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation<Devices<Elements>::value...>;
    };
    
    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation<Device<Elements>::value...>;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
};

template<typename Element>
struct Gauge<Element>
{
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Element>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation<Devices<Element>::value...>;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
};

}}

#endif