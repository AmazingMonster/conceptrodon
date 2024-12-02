// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNWILLFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNWILLFUL_H

#include "conceptrodon/omennivore/is_willful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unwillful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnwillful
=   Mouldivore::AnyDeceive<IsWillful, Args...>
||  AllUnwillful<Args...>
;

}}

#endif