// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_DAWNLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_DAWNLY_H

#include "conceptrodon/omennivore/concepts/descend/all_dawnly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyDawnly = (... || Dawnly<Structures>);

template<typename...Args>
concept AnyDawnly
=   JustAnyDawnly<Args...>
||  AllDawnly<Args...>;

}}

#endif