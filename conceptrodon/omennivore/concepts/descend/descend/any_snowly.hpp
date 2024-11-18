// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_SNOWLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_SNOWLY_H

#include "conceptrodon/omennivore/concepts/descend/all_snowly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnySnowly = (... || Snowly<Structures>);

template<typename...Args>
concept AnySnowly
=   JustAnySnowly<Args...>
||  AllSnowly<Args...>;

}}

#endif