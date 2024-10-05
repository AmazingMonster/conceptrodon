// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_REVERSE_H
#define CONCEPTRODON_PAGELIVORE_REVERSE_H

#include "conceptrodon/descend/microbiota/varbola/flip.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation=Shuttle>
struct Reverse
{
    template<auto...Variables>
    using Page = Omennivore::Send<typename Varbola::Flip<Variables...>::type>
    ::template UniRail<Operation>;
};

}}

#endif