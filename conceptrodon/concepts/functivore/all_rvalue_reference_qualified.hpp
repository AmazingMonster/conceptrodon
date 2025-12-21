// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_RVALUE_REFERENCE_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_ALL_RVALUE_REFERENCE_QUALIFIED_H

#include "conceptrodon/concepts/mouldivore/all_confess.hpp"
#include "conceptrodon/metafunctions/functivore/is_rvalue_reference.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllRvalueReferenceQualified
= Mouldivore::AllConfess<IsRvalueReference, Args...>;

}}

#endif