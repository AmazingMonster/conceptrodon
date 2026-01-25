// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_ALL_FAILED_H
#define CONCEPTRODON_PAGELIVORE_ALL_FAILED_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate, auto...Variables>
concept AllFailed = (...&& not static_cast<bool>(Predicate<Variables>::value));

}}

#endif