// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NICE_H
#define CONCEPTRODON_VARYBIVORE_NICE_H

#include "conceptrodon/metafunctions/varybivore/yes.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept Nice = Yes<Args...>::value;

}}

#endif