// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_FALSIFY_H
#define CONCEPTRODON_PAGELIVORE_FALSIFY_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate, auto...Variables>
concept Falsify = not Predicate<Variables...>::value;

}}

#endif