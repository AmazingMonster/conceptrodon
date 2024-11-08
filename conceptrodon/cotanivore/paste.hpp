// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_COTANIVORE_PASTE_H
#define CONCEPTRODON_COTANIVORE_PASTE_H

#include "conceptrodon/microbiota/cotanis/typical_paste.hpp"

namespace Conceptrodon {
namespace Cotanivore {

using Cotanis::TypicalPaste;

template<typename...PackedContainers>
using Paste = Cotanis::TypicalPaste<PackedContainers...>::type;

}}

#endif