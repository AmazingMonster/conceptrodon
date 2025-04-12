// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOEXCEPT_SPECIFIED_H
#define CONCEPTRODON_FUNCTIVORE_NOEXCEPT_SPECIFIED_H

#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/functivore/is_noexcept.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept NoexceptSpecified
= Mouldivore::Confess<IsNoexcept, F>;

}}

#endif