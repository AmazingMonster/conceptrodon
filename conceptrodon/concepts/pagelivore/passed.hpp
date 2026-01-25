// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_PASSED_H
#define CONCEPTRODON_PAGELIVORE_PASSED_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate, auto...Variables>
concept Passed = static_cast<bool>(Predicate<Variables...>::value);

}}

#endif