// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NICE_H
#define CONCEPTRODON_TYPELIVORE_NICE_H

#include "conceptrodon/metafunctions/typelivore/yes.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept Nice = Yes<Args...>::value;

}}

#endif