// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_REVEAL_H
#define CONCEPTRODON_ROADRIVORE_REVEAL_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct Reveal
{
    template<template<typename...> class...Containers>
    using Road = Operation<Containers...>::type;
};

}}

#endif