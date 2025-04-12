// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_GET_VARIADIC_TYPE_SIGNATURE_H
#define CONCEPTRODON_FUNCTIVORE_GET_VARIADIC_TYPE_SIGNATURE_H

#include "conceptrodon/functivore/analyzer.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename Fn>
struct TypicalGetVariadicTypeSignature
{ using type = Analyzer<Fn>::variadic_type_signature;};

template<typename...Args>
using GetVariadicTypeSignature = TypicalGetVariadicTypeSignature<Args...>::type;

}}
/******************************************************************************************************/

#endif
