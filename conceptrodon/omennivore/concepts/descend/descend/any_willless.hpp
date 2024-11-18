// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_WILLLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_WILLLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_willless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyWillless = (... || Willless<Structures>);

template<typename...Args>
concept AnyWillless
=   JustAnyWillless<Args...>
||  AllWillless<Args...>;

}}

#endif