// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_MOLDLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_MOLDLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_moldless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyMoldless = (... || Moldless<Structures>);

template<typename...Args>
concept AnyMoldless
=   JustAnyMoldless<Args...>
||  AllMoldless<Args...>;

}}

#endif