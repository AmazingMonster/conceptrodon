// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_HAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_HAILFUL_H

#include "conceptrodon/omennivore/is_hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_hailful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyHailful
=   Mouldivore::AnyConfess<IsHailful, Args...>
||  AllHailful<Args...>;

}}

#endif