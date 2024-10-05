// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_SITUATIONAL_H
#define CONCEPTRODON_MOULDIVORE_SITUATIONAL_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct Situational
{
    template<typename, typename>
    struct ProtoMold {};

    template <typename IfTrue, typename IfFalse>
    requires Predicate<IfTrue, IfFalse>::value
    struct ProtoMold<IfTrue, IfFalse> 
    { using type = IfTrue; };

    template<typename IfTrue, typename IfFalse>
    requires (not Predicate<IfTrue, IfFalse>::value)
    struct ProtoMold<IfTrue, IfFalse> 
    { using type = IfFalse; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    using Mold_t = ProtoMold<Args...>::type;
};

}}

#endif