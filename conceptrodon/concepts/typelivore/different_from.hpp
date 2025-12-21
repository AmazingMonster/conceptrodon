// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_DIFFERENT_FROM_H
#define CONCEPTRODON_TYPELIVORE_DIFFERENT_FROM_H

#include "conceptrodon/metafunctions/typelivore/is_different.hpp"
#include "conceptrodon/concepts/mouldivore/confess.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept DifferentFrom
=   Mouldivore::Confess<IsDifferent, LeftSide, RightSide>
&&  Mouldivore::Confess<IsDifferent, RightSide, LeftSide>;

}}

#endif