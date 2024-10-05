// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_AGENT_H
#define CONCEPTRODON_MOULDIVORE_AGENT_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    { using type = Operation<Elements...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif