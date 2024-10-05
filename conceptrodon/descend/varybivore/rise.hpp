// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_RISE_H
#define CONCEPTRODON_VARYBIVORE_RISE_H

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/descend/microbiota/varbola/arise.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Rise
{
    template<template<auto...> class...Agreements>
    using Rail = decltype(Varbola::arise<Agreements..., Variables...>())::type;

    template<template<auto...> class Operation=Shuttle>
    using UniRail = decltype(Varbola::arise<Operation, Variables...>())::type;
};

template<auto...Variables>
using Rise_t = Rise<Variables...>::template UniRail<>;

}}

#endif