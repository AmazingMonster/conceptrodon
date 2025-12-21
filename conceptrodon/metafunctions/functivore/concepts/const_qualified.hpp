// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_CONST_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_CONST_QUALIFIED_H

#include "conceptrodon/metafunctions/mouldivore/concepts/confess.hpp"
#include "conceptrodon/metafunctions/functivore/is_const.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept ConstQualified
= Mouldivore::Confess<IsConst, F>;

}}

#endif