// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PREEN_H
#define CONCEPTRODON_TYPELIVORE_PREEN_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Preen
{
    template<template<typename...> class Cosmetic>
    struct ProtoRoad 
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

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif