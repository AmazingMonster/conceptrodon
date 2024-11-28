// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_ANY_DECEIVE_H
#define CONCEPTRODON_PAGELIVORE_ANY_DECEIVE_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate<Elements::value>::value));

}}

#endif