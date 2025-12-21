// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_GET_RETURN_TYPE_H
#define CONCEPTRODON_FUNCTIVORE_GET_RETURN_TYPE_H

#include "conceptrodon/metafunctions/functivore/typical_get_return_type.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
using GetReturnType = TypicalGetReturnType<Args...>::type;

}}
/******************************************************************************************************/

#endif
