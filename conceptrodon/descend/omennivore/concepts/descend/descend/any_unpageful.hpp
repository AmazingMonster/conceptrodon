// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNPAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNPAGEFUL_H

#include "conceptrodon/omennivore/is_pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unpageful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyUnpageful
= (...||(not IsPageful<Args>::value));

template<typename...Args>
concept AnyUnpageful
=   JustAnyUnpageful<Args...>
||  AllUnpageful<Args...>
;

}}

#endif