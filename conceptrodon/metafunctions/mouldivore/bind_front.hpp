// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_BIND_FRONT_H
#define CONCEPTRODON_MOULDIVORE_BIND_FRONT_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct BindFront
{
    template<typename...Beginnings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Beginnings..., Elements...>;
    };

    template<typename...Beginnings>
    using Mold = ProtoMold<Beginnings...>;
};

}}

#endif