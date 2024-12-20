/************************/
/**** Implementation ****/
/************************/

template<auto Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate(Variables)));

/***************/
/**** Tests ****/
/***************/

/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** fun ****/
template<auto...Args>
requires AnyFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyFalsify<Pred_0, Args...> && AnyFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());