// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_WAREHIVORE_PASTE_H
#define CONCEPTRODON_WAREHIVORE_PASTE_H

#include "conceptrodon/metafunctions/warehivore/typical_paste.hpp"

namespace Conceptrodon {
namespace Warehivore {

template<typename...Packs>
using Paste = TypicalPaste<Packs...>::type;

}}

#endif