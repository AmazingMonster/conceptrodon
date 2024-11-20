// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_SNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_SNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_snowful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnySnowful
=   Mouldivore::AnyConfess<IsSnowful, Args...>
||  AllSnowful<Args...>;

}}

#endif