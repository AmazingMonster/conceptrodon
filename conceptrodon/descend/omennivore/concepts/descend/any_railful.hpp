// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_RAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_RAILFUL_H

#include "conceptrodon/omennivore/is_railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyRailful
=   Mouldivore::AnyConfess<IsRailful, Args...>
||  AllRailful<Args...>;

}}

#endif