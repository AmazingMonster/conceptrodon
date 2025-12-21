// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_TYPICAL_H
#define CONCEPTRODON_OMENNIVORE_ANY_TYPICAL_H

#include "conceptrodon/metafunctions/omennivore/concepts/all_typical.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyTypical = (... || Typical<Structures>);

template<typename...Args>
concept AnyTypical
=   JustAnyTypical<Args...>
||  AllTypical<Args...>;

}}

#endif