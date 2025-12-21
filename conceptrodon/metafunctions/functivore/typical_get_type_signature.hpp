// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_TYPICAL_GET_TYPE_SIGNATURE_H
#define CONCEPTRODON_FUNCTIVORE_TYPICAL_GET_TYPE_SIGNATURE_H

#include "conceptrodon/metafunctions/functivore/analyzer.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename Fn>
struct TypicalGetTypeSignature
{ using type = Analyzer<Fn>::type_signature;};

}}
/******************************************************************************************************/

#endif
