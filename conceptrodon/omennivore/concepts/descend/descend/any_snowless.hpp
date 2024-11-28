// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_SNOWLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_SNOWLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_snowless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnySnowless = (... || Snowless<Structures>);

template<typename...Args>
concept AnySnowless
=   JustAnySnowless<Args...>
||  AllSnowless<Args...>;

}}

#endif