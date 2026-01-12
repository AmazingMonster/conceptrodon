// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_AWAIT_H
#define CONCEPTRODON_CLXYOSTEON_AWAIT_H

#include "conceptrodon/regularities/clxyosteon/right_relate.hpp"
#include "conceptrodon/metafunctions/pagelivore/bi_cognate_gauge.hpp"
#include "conceptrodon/metafunctions/varybivore/all.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Clxyosteon {

template<template<typename...> class AwaitingPredicate>
struct Await
{
    template<template<typename...> class IncomingPredicate>
    struct ProtoRoad
    {
        template<typename...Args>
        using Mold = RightRelate
        <
                Pagelivore::BiCognateGauge<Varybivore::All>
                ::Road<AwaitingPredicate, IncomingPredicate>
                ::template Mold
        >
        ::template Mold<Args...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}
/******************************************************************************************************/

#endif