// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_GET_TYPE_SIGNATURE_H
#define CONCEPTRODON_FUNCTIVORE_GET_TYPE_SIGNATURE_H

#include "conceptrodon/metafunctions/functivore/typical_get_type_signature.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
using GetTypeSignature = TypicalGetTypeSignature<Args...>::type;

}}
/******************************************************************************************************/

#endif
