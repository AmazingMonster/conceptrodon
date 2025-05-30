/************************/
/**** Implementation ****/
/************************/

template<typename Predicate, auto...Variables>
concept Clarify = Predicate{}(Variables...);

/***************/
/**** Tests ****/
/***************/

/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** fun ****/
template<auto...Args>
requires Clarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Clarify<Pred_0, Args...> && Clarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());