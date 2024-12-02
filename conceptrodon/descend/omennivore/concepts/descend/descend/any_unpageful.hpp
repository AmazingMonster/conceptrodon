// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNPAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNPAGEFUL_H

#include "conceptrodon/omennivore/is_pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unpageful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnpageful
=   Mouldivore::AnyDeceive<IsPageful, Args...>
||  AllUnpageful<Args...>
;

}}

#endif