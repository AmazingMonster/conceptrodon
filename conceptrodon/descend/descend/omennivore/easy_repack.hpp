// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_REPACK_H
#define CONCEPTRODON_OMENNIVORE_EASY_REPACK_H

#include "conceptrodon/descend/omennivore/concepts/moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/railful.hpp"
#include "conceptrodon/descend/cotanivore/repack.hpp"
#include "conceptrodon/descend/sequnivore/repack.hpp"
#include "conceptrodon/descend/warehivore/repack.hpp"
#include "conceptrodon/descend/stockivore/repack.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
struct EasyRepack
: public Sequnivore::Repack<Packages...>
{};

template<typename...Packages>
requires (... && Moldful<Packages>)
struct EasyRepack<Packages...>
: public Cotanivore::Repack<Packages...>
{};

template<typename...Packages>
requires (... && Roadful<Packages>)
struct EasyRepack<Packages...>
: public Warehivore::Repack<Packages...>
{};

template<typename...Packages>
requires (... && Railful<Packages>)
struct EasyRepack<Packages...>
: public Stockivore::Repack<Packages...>
{};

}}

#endif