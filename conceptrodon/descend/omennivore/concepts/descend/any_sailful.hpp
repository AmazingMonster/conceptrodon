// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_SAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_SAILFUL_H

#include "conceptrodon/omennivore/is_sailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_sailful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnySailful
=   Mouldivore::AnyConfess<IsSailful, Args...>
||  AllSailful<Args...>;

}}

#endif