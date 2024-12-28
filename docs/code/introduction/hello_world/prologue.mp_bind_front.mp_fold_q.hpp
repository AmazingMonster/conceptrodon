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

using L = mp_list<mp_value<3>, mp_value<4>, mp_value<3>>;

template<typename...Args>
using BindL = mp_bind_front<mp_fold_q, L>
::fn<Args...>;

template<typename...Args>
using BindLV = mp_bind_front<mp_fold_q, L, V>
::fn<Args...>;

static_assert(std::same_as<
    BindL<V, Subtract>,
    mp_fold_q<L, V, Subtract>
>);

static_assert(std::same_as<
    BindLV<Subtract>,
    mp_fold_q<L, V, Subtract>
>);