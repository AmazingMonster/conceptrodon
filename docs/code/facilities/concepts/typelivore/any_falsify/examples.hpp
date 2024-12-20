/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return false;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return false;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<auto...Args>
requires (...||(not Pred_0{}(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0{}(Args))) && (...||(not Pred_1{}(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());