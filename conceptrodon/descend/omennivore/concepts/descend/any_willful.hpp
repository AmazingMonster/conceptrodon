// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_WILLFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_WILLFUL_H

#include "conceptrodon/omennivore/is_willful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_willful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyWillful = (... || IsWillful<Args>::value);

template<typename...Args>
concept AnyWillful
=   JustAnyWillful<Args...>
||  AllWillful<Args...>;

}}

#endif