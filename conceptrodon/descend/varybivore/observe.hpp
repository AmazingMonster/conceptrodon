// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_OBSERVE_H
#define CONCEPTRODON_VARYBIVORE_OBSERVE_H

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/descend/microbiota/varbola/stare.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<bool...Phenomena>
struct Observe
{
    template<template<auto...> class...Agreements>
    using Rail = decltype(Varbola::stare<Agreements..., Phenomena...>())::type;

    template<template<auto...> class Operation=Ark>
    using UniRail = decltype(Varbola::stare<Operation, Phenomena...>())::type;
};

template<bool...Phenomena>
using Observe_t = Observe<Phenomena...>::template UniRail<>;

}}

#endif