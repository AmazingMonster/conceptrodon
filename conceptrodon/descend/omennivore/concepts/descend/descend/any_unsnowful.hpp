// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNSNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNSNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unsnowful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyUnsnowful
= (...||(not IsSnowful<Args>::value));

template<typename...Args>
concept AnyUnsnowful
=   JustAnyUnsnowful<Args...>
||  AllUnsnowful<Args...>
;

}}

#endif