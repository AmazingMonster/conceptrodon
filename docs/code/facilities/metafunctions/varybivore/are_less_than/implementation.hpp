/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct AreLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Variables < Target)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Variables < Target)) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreLessThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<6, 2, 3>::value);