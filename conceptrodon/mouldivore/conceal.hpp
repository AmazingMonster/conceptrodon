// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_CONCEAL_H
#define CONCEPTRODON_MOULDIVORE_CONCEAL_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Conceal
{
    template<typename...Elements>
    struct ProtoMold
    { using type = Operation<Elements...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

}}

#endif