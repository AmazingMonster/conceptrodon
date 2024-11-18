// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNMOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNMOLDFUL_H

#include "conceptrodon/omennivore/is_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unmoldful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyUnmoldful
= (...||(not IsMoldful<Args>::value));

template<typename...Args>
concept AnyUnmoldful
=   JustAnyUnmoldful<Args...>
||  AllUnmoldful<Args...>
;

}}

#endif