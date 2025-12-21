// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_CONCEAL_H
#define CONCEPTRODON_ROADRIVORE_CONCEAL_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct Conceal
{
    template<template<typename...> class...Containers>
    struct ProtoRoad
    { using type = Operation<Containers...>; };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};

}}

#endif