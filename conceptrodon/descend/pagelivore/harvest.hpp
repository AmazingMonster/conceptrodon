// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_HARVEST_H
#define CONCEPTRODON_PAGELIVORE_HARVEST_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation=Shuttle>
struct Harvest
{ 
    template<typename...Crops>
    using Mold = Operation<Crops::value...>; 
};

}}

#endif