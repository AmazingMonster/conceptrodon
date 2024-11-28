// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_RISE_H
#define CONCEPTRODON_VARYBIVORE_RISE_H

#include "conceptrodon/descend/microbiota/varbola/arise.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Rise
{
    template<template<auto...> class...Agreements>
    using Rail = decltype(Varbola::arise<Agreements..., Variables...>())::type;
};

}}

#endif