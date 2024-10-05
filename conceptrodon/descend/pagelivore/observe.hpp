// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_OBSERVE_H
#define CONCEPTRODON_PAGELIVORE_OBSERVE_H

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/descend/microbiota/varbola/stare.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation=Ark>
struct Observe
{
    template<bool...Phenomena>
    using Page = decltype(Varbola::stare<Operation, Phenomena...>())::type;
};

}}

#endif