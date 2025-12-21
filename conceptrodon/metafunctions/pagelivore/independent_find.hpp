// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_INDEPENDENT_FIND_H
#define CONCEPTRODON_PAGELIVORE_INDEPENDENT_FIND_H

#include "conceptrodon/metafunctions/microbiota/pagelis/independent_find.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Predicates>
using IndependentFind = Pagelis::IndependentFind<Predicates...>;


}}

#endif