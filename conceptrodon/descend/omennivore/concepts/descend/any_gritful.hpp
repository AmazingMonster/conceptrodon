// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GRITFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_GRITFUL_H

#include "conceptrodon/omennivore/is_gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_gritful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyGritful = (... || IsGritful<Args>::value);

template<typename...Args>
concept AnyGritful
=   JustAnyGritful<Args...>
||  AllGritful<Args...>;

}}

#endif