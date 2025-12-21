// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_VALUABLE_H
#define CONCEPTRODON_OMENNIVORE_ANY_VALUABLE_H

#include "conceptrodon/metafunctions/omennivore/concepts/valuable.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyValuable
= (...||Valuable<Structures>);

template<typename...Args>
concept AnyValuable
=   JustAnyValuable<Args...>
||  AllValuable<Args...>;

}}

#endif