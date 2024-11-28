// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_HARVEST_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_HARVEST_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<Crops::value...>; 
};

}}

#endif