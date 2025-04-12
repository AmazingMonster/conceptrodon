// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_NOEXCEPT_SPECIFIED_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_NOEXCEPT_SPECIFIED_H

#include "conceptrodon/mouldivore/concepts/all_deceive.hpp"
#include "conceptrodon/functivore/is_noexcept.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotNoexceptSpecified
= Mouldivore::AllDeceive<IsNoexcept, Args...>;

}}

#endif