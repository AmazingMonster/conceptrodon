#include "boost/mp11.hpp"

using namespace boost;
using namespace mp11;

template<typename...>
struct Operation;

using SupposedResult = Operation
<
    mp_value<0>,
    mp_value<1>,
    mp_value<2>,
    mp_value<3>
>;

template<typename...Args>
using Metafunction = mp_bind_front
<
    Operation,
    mp_value<0>,
    mp_value<1>
>
::fn<Args...>;

using Result = Metafunction
<
    mp_value<2>,
    mp_value<3>
>;

static_assert(std::same_as<Result, SupposedResult>);