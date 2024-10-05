// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_FALSIFY_H
#define CONCEPTRODON_VARYBIVORE_FALSIFY_H

namespace Conceptrodon {
namespace Varybivore {

template<template<auto...> class Predicate, auto...Variables>
concept Falsify = not Predicate<Variables...>::value;

}}

#endif