// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_RVALUE_REFERENCE_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_RVALUE_REFERENCE_QUALIFIED_H

#include "conceptrodon/mouldivore/concepts/all_deceive.hpp"
#include "conceptrodon/functivore/is_rvalue_reference.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotRvalueReferenceQualified
= Mouldivore::AllDeceive<IsRvalueReference, Args...>;

}}

#endif