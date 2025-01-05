// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_DIFFERENT_FROM_H
#define CONCEPTRODON_TYPELIVORE_DIFFERENT_FROM_H

#include "conceptrodon/typelivore/is_different.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept DifferentFrom
=   Mouldivore::Confess<IsDifferent, LeftSide, RightSide>
&&  Mouldivore::Confess<IsDifferent, RightSide, LeftSide>;

}}

#endif