// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_INDEPENDENT_COGNATE_FIND_H
#define CONCEPTRODON_PAGELIVORE_INDEPENDENT_COGNATE_FIND_H

#include "conceptrodon/microbiota/pagelis/independent_cognate_find.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Sequences>
using IndependentCognateFind = Pagelis::IndependentCognateFind<Sequences...>;


}}

#endif