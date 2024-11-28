// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_HARVEST_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_HARVEST_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<typename Crops::type...>; 
};

}}

#endif