// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_BIND_BACK_H
#define CONCEPTRODON_PAGELIVORE_BIND_BACK_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct BindBack
{
    template<auto...Endings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Variables..., Endings...>;
    };

    template<auto...Endings>
    using Page = ProtoPage<Endings...>;
};

}}

#endif