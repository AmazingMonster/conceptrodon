// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_DAWNFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_DAWNFUL_H

#include "conceptrodon/omennivore/is_dawnful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_dawnful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyDawnful
=   Mouldivore::AnyConfess<IsDawnful, Args...>
||  AllDawnful<Args...>;

}}

#endif