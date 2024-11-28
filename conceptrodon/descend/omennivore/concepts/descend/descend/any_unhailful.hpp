// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNHAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNHAILFUL_H

#include "conceptrodon/omennivore/is_hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unhailful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnhailful
=   Mouldivore::AnyConfess<IsHailful, Args...>
||  AllUnhailful<Args...>
;

}}

#endif