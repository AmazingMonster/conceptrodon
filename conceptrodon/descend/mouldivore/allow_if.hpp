// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ALLOW_IF_H
#define CONCEPTRODON_MOULDIVORE_ALLOW_IF_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct AllowIf
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Elements>
    requires Predicate<Elements...>::value
    struct ProtoMold<Elements...>
    { using type = Capsule<Elements...>; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Elements>
    requires Predicate<Elements...>::value
    using Mold_t = Capsule<Elements...>;
};

}}

#endif