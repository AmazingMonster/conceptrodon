// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_CLASSIC_PLUME_H
#define CONCEPTRODON_TYPELIVORE_CLASSIC_PLUME_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct ClassicPlume
{
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Elements>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<typename Cosmetics<Elements>::type...>;
    };

    template<template<typename...> class Cosmetic>
    struct ProtoRoad<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetic<Elements>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<typename Cosmetic<Elements>::type...>;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

template<typename Element>
struct ClassicPlume<Element>
{
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Element>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<typename Cosmetics<Element>::type...>;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

}}

#endif