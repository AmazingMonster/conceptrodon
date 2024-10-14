// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_GRADE_H
#define CONCEPTRODON_TYPELIVORE_GRADE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Grade
{
    template<template<typename...> class Paper>
    struct ProtoRoad 
    { 
        template<template<auto...> class Operation>
        struct Detail
        {
            using type = Operation<Paper<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation<Paper<Elements>::value...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif