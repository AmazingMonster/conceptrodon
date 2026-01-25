// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ANY_PASSED_H
#define CONCEPTRODON_MOULDIVORE_ANY_PASSED_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate, typename...Elements>
concept AnyPassed = (...||static_cast<bool>(Predicate<Elements>::value));

}}

#endif