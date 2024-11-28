// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GRITFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_GRITFUL_H

#include "conceptrodon/omennivore/is_gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_gritful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyGritful
=   Mouldivore::AnyConfess<IsGritful, Args...>
||  AllGritful<Args...>;

}}

#endif