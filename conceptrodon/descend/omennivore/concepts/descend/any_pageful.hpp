// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_PAGEFUL_H

#include "conceptrodon/omennivore/is_pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_pageful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyPageful
=   Mouldivore::AnyConfess<IsPageful, Args...>
||  AllPageful<Args...>;

}}

#endif