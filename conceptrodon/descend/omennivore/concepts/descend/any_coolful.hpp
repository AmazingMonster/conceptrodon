// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_COOLFUL_H

#include "conceptrodon/omennivore/is_coolful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_coolful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyCoolful
=   Mouldivore::AnyConfess<IsCoolful, Args...>
||  AllCoolful<Args...>;

}}

#endif