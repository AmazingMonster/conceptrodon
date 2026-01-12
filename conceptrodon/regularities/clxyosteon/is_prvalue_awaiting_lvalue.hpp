// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_IS_PRVALUE_AWAITING_LVALUE_H
#define CONCEPTRODON_CLXYOSTEON_IS_PRVALUE_AWAITING_LVALUE_H

#include <type_traits>
#include "conceptrodon/regularities/clxyosteon/await.hpp"
#include "conceptrodon/metafunctions/mouldivore/negation.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Clxyosteon {

template<typename...Args>
using IsPrvalueAwaitingLvalue = Await<Mouldivore::Negation<std::is_reference>::Mold>
::Road<std::is_lvalue_reference>
::Mold<Args...>;

}}
/******************************************************************************************************/

#endif