// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_MOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_MOLDFUL_H

#include "conceptrodon/omennivore/is_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyMoldful = (... || IsMoldful<Args>::value);

template<typename...Args>
concept AnyMoldful
=   JustAnyMoldful<Args...>
||  AllMoldful<Args...>;

}}

#endif