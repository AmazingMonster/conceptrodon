// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PLUME_H
#define CONCEPTRODON_TYPELIVORE_PLUME_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Plume
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

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

}}

#endif