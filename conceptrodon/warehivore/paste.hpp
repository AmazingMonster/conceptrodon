// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_WAREHIVORE_PASTE_H
#define CONCEPTRODON_WAREHIVORE_PASTE_H

#include "conceptrodon/microbiota/waretus/typical_paste.hpp"

namespace Conceptrodon {
namespace Warehivore {

using Waretus::TypicalPaste;

template<typename...Packs>
using Paste = Waretus::TypicalPaste<Packs...>::type;

}}

#endif