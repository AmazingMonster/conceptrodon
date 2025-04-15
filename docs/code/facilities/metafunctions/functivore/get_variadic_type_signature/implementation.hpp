/**********************/
/**** Dependencies ****/
/**********************/

/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...)>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...) const>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn> {};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn> {};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())> {};

/**** TypicalGetVariadicTypeSignature ****/
template<typename Fn>
struct TypicalGetVariadicTypeSignature
{ using type = Analyzer<Fn>::variadic_type_signature;};

/************************/
/**** Implementation ****/
/************************/

template<typename...Args>
using GetVariadicTypeSignature = TypicalGetVariadicTypeSignature<Args...>::type;

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** functions ****/
inline int fun(int, int*){ return 0; }
inline int variadic_fun(int, int*...){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;
using VariadicAbominableFun = int(int, int*...) const;

/**** function pointers ****/
inline auto FunAddr { &fun };
inline auto VariadicFunAddr { &variadic_fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
    inline int variadic_fun(int, int*...) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

struct VariadicFO
{
    int operator()(int, int*...) const { return 0; }
};

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);
using SupposedVariadicTypeSignature = int(int, int*...);

/**** Tests ****/
static_assert(std::same_as<GetVariadicTypeSignature<decltype(fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<AbominableFun>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(FunAddr)>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(&Tester::fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<FO>, SupposedTypeSignature>);

static_assert(std::same_as<GetVariadicTypeSignature<decltype(variadic_fun)>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<VariadicAbominableFun>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(VariadicFunAddr)>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(&Tester::variadic_fun)>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<VariadicFO>, SupposedVariadicTypeSignature>);
