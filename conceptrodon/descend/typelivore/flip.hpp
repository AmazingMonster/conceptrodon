// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_FLIP_H
#define CONCEPTRODON_TYPELIVORE_FLIP_H

#include "conceptrodon/descend/microbiota/typella/typical_flip.hpp"

namespace Conceptrodon {
namespace Typelivore {

using Typella::TypicalFlip;

template<typename...Elements>
using Flip = Typella::TypicalFlip<Elements...>::type;

}}

#endif