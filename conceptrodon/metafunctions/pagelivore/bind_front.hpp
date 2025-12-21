// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_BIND_FRONT_H
#define CONCEPTRODON_PAGELIVORE_BIND_FRONT_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct BindFront
{
    template<auto...Beginnings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Beginnings..., Variables...>;
    };

    template<auto...Beginnings>
    using Page = ProtoPage<Beginnings...>;
};

}}

#endif