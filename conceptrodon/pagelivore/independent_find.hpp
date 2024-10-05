// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_INDEPENDENT_FIND_H
#define CONCEPTRODON_PAGELIVORE_INDEPENDENT_FIND_H

#include "conceptrodon/microbiota/pagelis/find.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Sequences>
using IndependentFind = Pagelis::Find<Sequences...>;


}}

#endif