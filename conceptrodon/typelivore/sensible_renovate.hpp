// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_RENOVATE_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_RENOVATE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SensibleRenovate
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<template<typename...> class...Decorations>
        using Road = Operation<Decorations<Elements>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif