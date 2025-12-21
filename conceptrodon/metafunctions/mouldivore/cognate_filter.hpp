// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_FILTER_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_FILTER_H

#include "conceptrodon/metafunctions/mouldivore/sieve.hpp"
#include "conceptrodon/metafunctions/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateFilter
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Omennivore::Send<typename Sieve<Predicates...>::template Mold<Elements...>>
        ::template UniRoad<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif