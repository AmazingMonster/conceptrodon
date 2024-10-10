// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_REVEAL_H
#define CONCEPTRODON_MOULDIVORE_REVEAL_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Reveal
{
    template<typename...Elements>
    using Mold = Operation<Elements...>::type;
};

}}

#endif