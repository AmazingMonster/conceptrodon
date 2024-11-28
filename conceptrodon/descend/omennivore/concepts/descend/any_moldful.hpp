// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_MOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_MOLDFUL_H

#include "conceptrodon/omennivore/is_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyMoldful
=   Mouldivore::AnyConfess<IsMoldful, Args...>
||  AllMoldful<Args...>;

}}

#endif