// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RISE_H
#define CONCEPTRODON_PAGELIVORE_RISE_H

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/descend/microbiota/varbola/arise.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation=Shuttle>
struct Rise
{
    template<auto...Variables>
    using Page = decltype(Varbola::arise<Operation, Variables...>())::type;
};

}}

#endif