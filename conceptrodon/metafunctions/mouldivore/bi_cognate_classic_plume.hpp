// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_BI_COGNATE_CLASSIC_PLUME_H
#define CONCEPTRODON_MOULDIVORE_BI_COGNATE_CLASSIC_PLUME_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct BiCognateClassicPlume
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        template<auto...Elements>
        struct Detail
        {
            using type = Operation<typename Devices<Elements>::type...>;
        };

        template<auto Element>
        struct Detail<Element>
        {
            using type = Operation<typename Devices<Element>::type...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class Device>
    struct ProtoRail<Device>
    {
        template<auto...Elements>
        struct Detail
        {
            using type = Operation<typename Device<Elements>::type...>;
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
            using type = Operation<typename Devices<Elements>::type...>;
        };

        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<typename Devices<Element>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    {
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<typename Device<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif