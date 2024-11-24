// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_OBSERVE_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_OBSERVE_H

#include "conceptrodon/descend/microbiota/varbola/stare.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateObserve
{
    template<auto...Phenomena>
    using Page = decltype
    (Varbola::stare<Operation, static_cast<bool>(Phenomena)...>())
    ::type;
};

}}

#endif