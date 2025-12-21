// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SEQUNIVORE_PASTE_H
#define CONCEPTRODON_SEQUNIVORE_PASTE_H

#include "conceptrodon/metafunctions/sequnivore/typical_paste.hpp"

namespace Conceptrodon {
namespace Sequnivore {

template<typename...Packs>
using Paste = TypicalPaste<Packs...>::type;

}}

#endif