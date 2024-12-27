/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct AreGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Target < Variables)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Target < Variables)) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreGreaterThan<1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3>::value);