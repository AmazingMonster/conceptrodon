// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_NOEXCEPT_SPECIFIED_H
#define CONCEPTRODON_FUNCTIVORE_NOT_NOEXCEPT_SPECIFIED_H

#include "conceptrodon/concepts/mouldivore/deceive.hpp"
#include "conceptrodon/metafunctions/functivore/is_noexcept.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept NotNoexceptSpecified
= Mouldivore::Deceive<IsNoexcept, F>;

}}

#endif