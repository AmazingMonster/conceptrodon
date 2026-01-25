// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ANY_FAILED_H
#define CONCEPTRODON_MOULDIVORE_ANY_FAILED_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate, typename...Elements>
concept AnyFailed = (...||(not static_cast<bool>(Predicate<Elements>::value)));

}}

#endif