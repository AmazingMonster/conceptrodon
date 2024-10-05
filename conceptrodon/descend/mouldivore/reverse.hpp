// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_REVERSE_H
#define CONCEPTRODON_MOULDIVORE_REVERSE_H

#include "conceptrodon/descend/microbiota/typella/flip.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation=Capsule>
struct Reverse
{
    template<typename...Elements>
    using Mold = Omennivore::Send<typename Typella::Flip<Elements...>::type>
    ::template UniRoad<Operation>;
};

}}

#endif