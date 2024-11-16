// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_PASTE_H
#define CONCEPTRODON_OMENNIVORE_EASY_PASTE_H

#include "conceptrodon/descend/omennivore/concepts/moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/railful.hpp"
#include "conceptrodon/cotanivore/paste.hpp"
#include "conceptrodon/sequnivore/paste.hpp"
#include "conceptrodon/warehivore/paste.hpp"
#include "conceptrodon/stockivore/paste.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
struct TypicalEasyPaste
{ using type = Sequnivore::Paste<Packages...>; };

template<typename...Packages>
requires (... && Moldful<Packages>)
struct TypicalEasyPaste<Packages...>
{ using type = Cotanivore::Paste<Packages...>; };

template<typename...Packages>
requires (... && Roadful<Packages>)
struct TypicalEasyPaste<Packages...>
{ using type = Warehivore::Paste<Packages...>; };

template<typename...Packages>
requires (... && Railful<Packages>)
struct TypicalEasyPaste<Packages...>
{ using type = Stockivore::Paste<Packages...>; };

template<typename...Packables>
using EasyPaste = TypicalEasyPaste<Packables...>::type;

}}

#endif