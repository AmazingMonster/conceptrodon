// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_CONJURE_SET_H
#define CONCEPTRODON_TYPELIVORE_CONJURE_SET_H

#include "conceptrodon/metafunctions/typelivore/typical_conjure_set.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;

}}

#endif