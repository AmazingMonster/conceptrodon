// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_BIND_BACK_H
#define CONCEPTRODON_MOULDIVORE_BIND_BACK_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct BindBack
{
    template<typename...Endings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Elements..., Endings...>;
    };

    template<typename...Endings>
    using Mold = ProtoMold<Endings...>;
};

}}

#endif