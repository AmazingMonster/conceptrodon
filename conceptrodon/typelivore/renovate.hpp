// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_RENOVATE_H
#define CONCEPTRODON_TYPELIVORE_RENOVATE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Renovate
{
    template<template<typename...> class...Decorations>
    struct ProtoRoad
    {
        template<template<typename...> class Operation>
        struct Detail
        { 
            using type = Operation<Decorations<Elements>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<Decorations<Elements>...>;
    };

    template<template<typename...> class...Decorations>
    using Road = ProtoRoad<Decorations...>;
};

}}

#endif