// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNMOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNMOLDFUL_H

#include "conceptrodon/omennivore/is_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unmoldful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnmoldful
=   Mouldivore::AnyDeceive<IsMoldful, Args...>
||  AllUnmoldful<Args...>
;

}}

#endif