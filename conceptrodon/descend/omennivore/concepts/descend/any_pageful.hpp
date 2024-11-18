// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_PAGEFUL_H

#include "conceptrodon/omennivore/is_pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_pageful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyPageful = (... || IsPageful<Args>::value);

template<typename...Args>
concept AnyPageful
=   JustAnyPageful<Args...>
||  AllPageful<Args...>;

}}

#endif