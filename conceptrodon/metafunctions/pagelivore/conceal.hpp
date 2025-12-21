// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_CONCEAL_H
#define CONCEPTRODON_PAGELIVORE_CONCEAL_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Conceal
{
    template<auto...Variables>
    struct ProtoPage
    { using type = Operation<Variables...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

}}

#endif