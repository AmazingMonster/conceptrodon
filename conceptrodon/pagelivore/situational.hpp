// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SITUATIONAL_H
#define CONCEPTRODON_PAGELIVORE_SITUATIONAL_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Predicates>
struct Situational
{
    template<auto IfTrue, auto IfFalse, auto...Others>
    struct ProtoPage
    { static constexpr auto value = IfFalse; };

    template<auto IfTrue, auto IfFalse, auto...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoPage<IfTrue, IfFalse, Others...> 
    { static constexpr auto value = IfTrue; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v
    { ProtoPage<Args...>::value };
};

}}

#endif