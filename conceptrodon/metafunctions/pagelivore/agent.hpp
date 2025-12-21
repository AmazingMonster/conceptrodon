// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_AGENT_H
#define CONCEPTRODON_PAGELIVORE_AGENT_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    { using type = Operation<Variables...>; };
    
    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    { using type = Operation<Variables...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif