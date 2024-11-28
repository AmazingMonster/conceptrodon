// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_CALMFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_CALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_calmful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyCalmful
=   Mouldivore::AnyConfess<IsCalmful, Args...>
||  AllCalmful<Args...>;

}}

#endif