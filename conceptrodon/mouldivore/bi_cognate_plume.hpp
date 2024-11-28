// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_BI_COGNATE_PLUME_H
#define CONCEPTRODON_MOULDIVORE_BI_COGNATE_PLUME_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct BiCognatePlume
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        template<auto...Elements>
        struct Detail
        {
            using type = Operation<Devices<Elements>...>;
        };

        template<auto Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>...>;
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
            using type = Operation<Device<Elements>...>;
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
            using type = Operation<Devices<Elements>...>;
        };

        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>...>;
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
            using type = Operation<Device<Elements>...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif