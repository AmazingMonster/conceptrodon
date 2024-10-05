// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_PERMIT_IF_H
#define CONCEPTRODON_MOULDIVORE_PERMIT_IF_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct PermitIf
{
    template<typename>
    struct ProtoMold {};

    template<typename Element>
    requires Predicate<Element>::value
    struct ProtoMold<Element>
    { using type = Element; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    using Mold_t = ProtoMold<Args...>::type;

    template<typename Element>
    requires Predicate<Element>::value
    using UniMold = Element;
};

}}

#endif