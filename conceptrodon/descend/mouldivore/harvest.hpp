// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_HARVEST_H
#define CONCEPTRODON_MOULDIVORE_HARVEST_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation=Capsule>
struct Harvest
{ 
    template<typename...Crops>
    using Mold = Operation<typename Crops::type...>; 
};

}}

#endif