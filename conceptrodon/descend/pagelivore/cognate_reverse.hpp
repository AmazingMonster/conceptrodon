// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_REVERSE_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_REVERSE_H

#include "conceptrodon/descend/microbiota/varbola/typical_turn_over.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateReverse
{
    template<auto...Variables>
    using Page = Omennivore::Send<typename Varbola::TypicalTurnOver<Variables...>::type>
    ::template UniRail<Operation>;
};

}}

#endif