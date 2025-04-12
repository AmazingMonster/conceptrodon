// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_CONST_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_NOT_CONST_QUALIFIED_H

#include "conceptrodon/mouldivore/concepts/deceive.hpp"
#include "conceptrodon/functivore/is_const.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept NotConstQualified
= Mouldivore::Deceive<IsConst, F>;

}}

#endif