// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_REVEAL_H
#define CONCEPTRODON_RAILLIVORE_REVEAL_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct Reveal
{
    template<template<auto...> class...Sequences>
    using Page = Operation<Sequences...>::type;
};

}}

#endif