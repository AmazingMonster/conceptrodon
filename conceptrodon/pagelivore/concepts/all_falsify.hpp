// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_ALL_FALSIFY_H
#define CONCEPTRODON_PAGELIVORE_ALL_FALSIFY_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate, auto...Variables>
concept AllFalsify = (...&&(not Predicate<Variables>::value));

}}

#endif