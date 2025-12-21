// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_GAUGE_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_GAUGE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<typename...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Elements>::value...>;
        };
        
        template<template<typename...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Elements>::value...>;
        };

        template<template<typename...> class...Devices>
        using Road = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<typename Element>
struct SensibleGauge<Element>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<typename...> class...Devices>
        using Road = Operation
        <Devices<Element>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif