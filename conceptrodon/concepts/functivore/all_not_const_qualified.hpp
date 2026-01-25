// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_CONST_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_CONST_QUALIFIED_H

#include "conceptrodon/concepts/mouldivore/all_failed.hpp"
#include "conceptrodon/metafunctions/functivore/is_const.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotConstQualified
= Mouldivore::AllFailed<IsConst, Args...>;

}}

#endif