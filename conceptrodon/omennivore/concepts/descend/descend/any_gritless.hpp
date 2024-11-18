// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GRITLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_GRITLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_gritless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyGritless = (... || Gritless<Structures>);

template<typename...Args>
concept AnyGritless
=   JustAnyGritless<Args...>
||  AllGritless<Args...>;

}}

#endif