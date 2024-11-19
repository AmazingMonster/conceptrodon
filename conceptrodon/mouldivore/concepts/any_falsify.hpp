// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_FALSIFY_H
#define CONCEPTRODON_TYPELIVORE_ANY_FALSIFY_H

namespace Conceptrodon {
namespace Typelivore {

template<template<typename...> class Predicate, typename...Elements>
concept AnyFalsify = (...||(not Predicate<Elements>::value));

}}

#endif