// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GRITLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_GRITLY_H

#include "conceptrodon/omennivore/concepts/descend/all_gritly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyGritly = (... || Gritly<Structures>);

template<typename...Args>
concept AnyGritly
=   JustAnyGritly<Args...>
||  AllGritly<Args...>;

}}

#endif