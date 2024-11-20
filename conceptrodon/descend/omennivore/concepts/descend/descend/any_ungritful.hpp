// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNGRITFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNGRITFUL_H

#include "conceptrodon/omennivore/is_gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_ungritful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUngritful
=   Mouldivore::AnyConfess<IsGritful, Args...>
||  AllUngritful<Args...>
;

}}

#endif