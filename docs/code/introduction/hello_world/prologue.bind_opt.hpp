#include "boost/mp11.hpp"

using namespace boost;
using namespace mp11;

struct Subtract
{
    template<typename A, typename B>
    using fn = mp_value<A::value - B::value>;
};

using V = mp_value<1>;

using Arg_0 = mp_value<3>;
using Arg_1 = mp_value<4>;
using Arg_2 = mp_value<3>;

using L = mp_list<Arg_0, Arg_1, Arg_2>;

template<typename V, typename Q>
struct QuotedFoldQ
{
    template<typename...Args>
    using fn = mp_fold_q<mp_list<Args...>, V, Q>;
};

template<typename...Args>
using BindOpt = mp_bind_front
<
    QuotedFoldQ<V, Subtract>::fn,
    Arg_0, Arg_1
>
::fn<Args...>;

static_assert(std::same_as<
    BindOpt<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);