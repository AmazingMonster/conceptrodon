// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_DECEIVE_H
#define CONCEPTRODON_MOULDIVORE_DECEIVE_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate, typename...Elements>
concept Deceive = not Predicate<Elements...>::value;

}}

#endif