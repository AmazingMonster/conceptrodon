// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_INDEPENDENT_FIND_H
#define CONCEPTRODON_MOULDIVORE_INDEPENDENT_FIND_H

#include "conceptrodon/metafunctions/microbiota/moldiae/independent_find.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Predicates>
using IndependentFind = Moldiae::IndependentFind<Predicates...>;

}}

#endif