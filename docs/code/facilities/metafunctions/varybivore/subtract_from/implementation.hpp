/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct SubtractFrom
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Target -...- Variables)}; 
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v
    {(Target -...- Variables)};
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Variables>
using Metafunction = SubtractFrom<3>::Page<Variables...>;

/**** Test ****/
static_assert(Metafunction<1, 2, -2, 2>::value == 0);