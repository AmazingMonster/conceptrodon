// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ALL_DECEIVE_H
#define CONCEPTRODON_MOULDIVORE_ALL_DECEIVE_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate<Elements>::value));

}}

#endif