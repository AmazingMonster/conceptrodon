/************************/
/**** Implementation ****/
/************************/

template<typename Predicate, typename...Elements>
concept AllConfess = (...&&Predicate{}(Elements::value));

/***************/
/**** Tests ****/
/***************/

/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());