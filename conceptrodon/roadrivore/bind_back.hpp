// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_BIND_BACK_H
#define CONCEPTRODON_ROADRIVORE_BIND_BACK_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct BindBack
{
    template<template<typename...> class...Endings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Containers..., Endings...>;
    };

    template<template<typename...> class...Endings>
    using Road = ProtoRoad<Endings...>;
};

}}

#endif