// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_CONCEAL_H
#define CONCEPTRODON_RAILLIVORE_CONCEAL_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct Conceal
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    { using type = Operation<Sequences...>; };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
};

}}

#endif