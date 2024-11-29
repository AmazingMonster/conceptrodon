// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_AGENT_H
#define CONCEPTRODON_ROADRIVORE_AGENT_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
    struct Detail<Warehouse<Containers...>>
    { using type = Operation<Containers...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif