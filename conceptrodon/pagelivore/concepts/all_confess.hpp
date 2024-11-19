// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_ALL_CONFESS_H
#define CONCEPTRODON_PAGELIVORE_ALL_CONFESS_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate, typename...Elements>
concept AllConfess = (...&&Predicate<Elements::value>::value);

}}

#endif