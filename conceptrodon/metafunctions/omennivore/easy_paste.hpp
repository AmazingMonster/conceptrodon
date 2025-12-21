// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_PASTE_H
#define CONCEPTRODON_OMENNIVORE_EASY_PASTE_H

#include "conceptrodon/metafunctions/omennivore/easy_typical_paste.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
using EasyPaste = EasyTypicalPaste<Packages...>::type;

}}

#endif