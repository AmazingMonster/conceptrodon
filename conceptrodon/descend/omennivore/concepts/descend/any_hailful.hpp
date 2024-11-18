// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_HAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_HAILFUL_H

#include "conceptrodon/omennivore/is_hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_hailful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyHailful = (... || IsHailful<Args>::value);

template<typename...Args>
concept AnyHailful
=   JustAnyHailful<Args...>
||  AllHailful<Args...>;

}}

#endif