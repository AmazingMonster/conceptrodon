// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_CONST_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_ALL_CONST_QUALIFIED_H

#include "conceptrodon/mouldivore/concepts/all_confess.hpp"
#include "conceptrodon/functivore/is_const.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllConstQualified
= Mouldivore::AllConfess<IsConst, Args...>;

}}

#endif