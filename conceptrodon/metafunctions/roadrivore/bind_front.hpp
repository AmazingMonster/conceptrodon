// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_BIND_FRONT_H
#define CONCEPTRODON_ROADRIVORE_BIND_FRONT_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct BindFront
{
    template<template<typename...> class...Beginnings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Beginnings..., Containers...>;
    };

    template<template<typename...> class...Beginnings>
    using Road = ProtoRoad<Beginnings...>;
};

}}

#endif