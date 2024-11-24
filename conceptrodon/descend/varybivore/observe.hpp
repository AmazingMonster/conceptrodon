// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_OBSERVE_H
#define CONCEPTRODON_VARYBIVORE_OBSERVE_H

#include "conceptrodon/descend/microbiota/varbola/stare.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Phenomena>
struct Observe
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (Varbola::stare<Agreements..., static_cast<bool>(Phenomena)...>())
    ::type;
};

}}

#endif