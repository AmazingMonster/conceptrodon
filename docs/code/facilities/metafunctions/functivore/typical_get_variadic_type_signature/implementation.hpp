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

/************************/
/**** Implementation ****/
/************************/

template<typename Fn>
struct TypicalGetVariadicTypeSignature
{ using type = Analyzer<Fn>::variadic_type_signature;};

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
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<AbominableFun>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunAddr)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO>::type, SupposedTypeSignature>);

static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(variadic_fun)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<VariadicAbominableFun>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(VariadicFunAddr)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::variadic_fun)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<VariadicFO>::type, SupposedVariadicTypeSignature>);
