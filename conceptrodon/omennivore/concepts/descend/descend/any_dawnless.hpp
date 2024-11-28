// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_DAWNLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_DAWNLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_dawnless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyDawnless = (... || Dawnless<Structures>);

template<typename...Args>
concept AnyDawnless
=   JustAnyDawnless<Args...>
||  AllDawnless<Args...>;

}}

#endif