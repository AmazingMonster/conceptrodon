// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_FILTER_H
#define CONCEPTRODON_MOULDIVORE_FILTER_H

#include "conceptrodon/descend/mouldivore/sieve.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation=Capsule>
struct Filter
{
    template<template<typename...> class Predicate>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Omennivore::Send<typename Sieve<Predicate>::template Mold_t<Elements...>>
        ::template UniRoad<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif