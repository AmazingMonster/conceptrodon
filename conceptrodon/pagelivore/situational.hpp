// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SITUATIONAL_H
#define CONCEPTRODON_PAGELIVORE_SITUATIONAL_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct Situational
{
    template<auto, auto>
    struct ProtoPage {};

    template<auto IfTrue, auto IfFalse>
    requires Predicate<IfTrue, IfFalse>::value
    struct ProtoPage<IfTrue, IfFalse> 
    { static constexpr auto value = IfTrue; };

    template<auto IfTrue, auto IfFalse>
    requires (not Predicate<IfTrue, IfFalse>::value)
    struct ProtoPage<IfTrue, IfFalse> 
    { static constexpr auto value = IfFalse; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v { ProtoPage<Args...>::value };
};

}}

#endif