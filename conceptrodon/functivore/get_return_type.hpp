// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_GET_RETURN_TYPE_H
#define CONCEPTRODON_FUNCTIVORE_GET_RETURN_TYPE_H

#include "conceptrodon/functivore/analyzer.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename Fn>
struct TypicalGetReturnType
{ using type = Analyzer<Fn>::result_type;};

template<typename...Args>
using GetReturnType = TypicalGetReturnType<Args...>::type;

}}
/******************************************************************************************************/

#endif
