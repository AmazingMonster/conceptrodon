// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_MOLDLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_MOLDLY_H

#include "conceptrodon/omennivore/concepts/descend/all_moldly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyMoldly = (... || Moldly<Structures>);

template<typename...Args>
concept AnyMoldly
=   JustAnyMoldly<Args...>
||  AllMoldly<Args...>;

}}

#endif