// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_SNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_SNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_snowful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnySnowful = (... || IsSnowful<Args>::value);

template<typename...Args>
concept AnySnowful
=   JustAnySnowful<Args...>
||  AllSnowful<Args...>;

}}

#endif