// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_SITUATIONAL_H
#define CONCEPTRODON_MOULDIVORE_SITUATIONAL_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Predicates>
struct Situational
{
    template<typename IfTrue, typename IfFalse, typename...>
    struct Detail
    { using type = IfFalse; };

    template <typename IfTrue, typename IfFalse, typename...Others>
    requires (...&& Predicates<IfTrue, IfFalse, Others...>::value)
    struct Detail<IfTrue, IfFalse, Others...>
    { using type = IfTrue; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif