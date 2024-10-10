// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_SAIL_DETRACT_H
#define CONCEPTRODON_ROADRIVORE_SAIL_DETRACT_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct SailDetract
{
    template<typename Negotiation>
    struct ProtoMold
    {
        template<template<typename...> class...Agreements>
        using Mold = Omennivore::Send<typename Operation<Agreements...>::type>::template UniZest<Negotiation::template Sail>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif