// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_COTANIVORE_PASTE_H
#define CONCEPTRODON_COTANIVORE_PASTE_H

#include "conceptrodon/metafunctions/cotanivore/typical_paste.hpp"

namespace Conceptrodon {
namespace Cotanivore {

template<typename...PackedContainers>
using Paste = TypicalPaste<PackedContainers...>::type;

}}

#endif