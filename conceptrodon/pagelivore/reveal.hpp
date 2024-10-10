// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_REVEAL_H
#define CONCEPTRODON_PAGELIVORE_REVEAL_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Reveal
{
    template<auto...Variables>
    using Page = Operation<Variables...>::type;
};

}}

#endif