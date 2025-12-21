// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_REVERSE_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_REVERSE_H

#include "conceptrodon/metafunctions/microbiota/typella/typical_turn_over.hpp"
#include "conceptrodon/metafunctions/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateReverse
{
    template<typename...Elements>
    using Mold = Omennivore::Send<typename Typella::TypicalTurnOver<Elements...>::type>
    ::template UniRoad<Operation>;
};

}}

#endif