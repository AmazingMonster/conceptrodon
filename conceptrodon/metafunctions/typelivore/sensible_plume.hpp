// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_PLUME_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_PLUME_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Elements>...>;
        };

        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Elements>...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename Element>
struct SensiblePlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<typename...> class...Cosmetics>
        using Road = Operation<Cosmetics<Element>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif