/************************/
/**** Implementation ****/
/************************/

template<typename Leader>
struct Follow
{
    template<typename Follower>
    struct Detail
    {
        using type = Follower;
    };

    template<auto Follower>
    struct ProtoPage
    {
        static constexpr auto value {Follower};
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Vay ****/
template<auto>
struct Vay {};

/**** Operation ****/
template<typename...Args>
struct Operation {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Operation<typename Follow<Args>::template Mold<int>...>;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int, int, int>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** Operation ****/
template<auto...Args>
struct Operation_1 {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction_1 = Operation_1<Follow<Args>::template Page<0>::value...>;

/**** SupposedResult ****/
using SupposedResult_1 = Operation_1<0, 0, 0, 0>;

/**** Result ****/
using Result_1 = Metafunction_1<Vay<0>, Vay<1>, Vay<2>, Vay<3>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);