/**********************/
/**** Dependencies ****/
/**********************/

#include <iostream>

/************************/
/**** Implementation ****/
/************************/

template<typename Target>
struct CopyLvalueToPrvalueWhileForwardOthers
{
    constexpr decltype(auto) operator()(std::remove_reference_t<Target>& arg)
    {
        if constexpr (not std::is_reference_v<Target>)
        {
            return static_cast<std::remove_cvref_t<Target>>(arg);
        }

        else
        {
            return static_cast<Target&&>(arg);
        }
    }
};

template<typename Target>
requires (not std::is_lvalue_reference_v<Target>)
struct CopyLvalueToPrvalueWhileForwardOthers<Target>
{
    constexpr decltype(auto) operator()(std::remove_reference_t<Target>& arg)
    {
        if constexpr (not std::is_reference_v<Target>)
        {
            return static_cast<std::remove_cvref_t<Target>>(arg);
        }

        else
        {
            return static_cast<Target&&>(arg);
        }
    }

    constexpr decltype(auto) operator()(std::remove_reference_t<Target>&& arg)
    {
        return static_cast<Target&&>(arg);
    }
};

/***********************/
/**** First Example ****/
/***********************/

#define CHECK_VIABILITY 0
#if CHECK_VIABILITY
#define BLANKET(...) __VA_ARGS__
#else
#define BLANKET(...)
#endif

/**** Argument ****/
struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    {
        std::cout << "Argument copy constructed" << std::endl;
    }
    
    Argument(Argument && argument)
    {
        std::cout << "Argument move constructed" << std::endl;
    }
};

/**** check****/
inline void check(Argument){}


/**** Test ****/
inline void test_copy_lvalue_to_prvalue_while_forward_others()
{
    Argument arg{};

    /**** Argument ****/

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument>: Passing LValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument>{}(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument>: Passing XValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument>{}(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument>: Passing PRValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument>{}(Argument{}));
    }

    std::cout << std::endl;

    /**** Argument& ****/

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&>: Passing LValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&>{}(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&>: Passing XValue ****/" << std::endl;
        BLANKET(check(CopyLvalueToPrvalueWhileForwardOthers<Argument&>{}(std::move(arg))));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&>: Passing PRValue ****/" << std::endl;
        BLANKET(check(CopyLvalueToPrvalueWhileForwardOthers<Argument&>{}(Argument{})));
    }

    std::cout << std::endl;

    /**** Argument&& ****/

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&&>: Passing LValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&&>{}(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&&>: Passing XValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&&>{}(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** CopyLvalueToPrvalueWhileForwardOthers<Argument&&>: Passing PRValue ****/" << std::endl;
        check(CopyLvalueToPrvalueWhileForwardOthers<Argument&&>{}(Argument{}));
    }
}

#undef BLANKET
#undef CHECK_VIABILITY

/************************/
/**** Second Example ****/
/************************/

#define CHECK_VIABILITY 0
#if CHECK_VIABILITY
#define BLANKET(...) __VA_ARGS__
#else
#define BLANKET(...)
#endif

/**** Test ****/
inline void test_std_forword()
{
    Argument arg{};

    {
        std::cout << "/**** std::forward<Argument>: Passing LValue ****/" << std::endl;
        check(std::forward<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument>: Passing XValue ****/" << std::endl;
        check(std::forward<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument>: Passing PRValue ****/" << std::endl;
        check(std::forward<Argument>(Argument{}));
    }

    std::cout << std::endl;

    /**** Argument& ****/

    {
        std::cout << "/**** std::forward<Argument&>: Passing LValue ****/" << std::endl;
        check(std::forward<Argument&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&>: Passing XValue ****/" << std::endl;
        BLANKET(check(std::forward<Argument&>(std::move(arg))));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&>: Passing PRValue ****/" << std::endl;
        BLANKET(check(std::forward<Argument&>(Argument{})));
    }

    std::cout << std::endl;

    /**** Argument&& ****/

    {
        std::cout << "/**** std::forward<Argument&&>: Passing LValue ****/" << std::endl;
        check(std::forward<Argument&&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&&>: Passing XValue ****/" << std::endl;
        check(std::forward<Argument&&>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward<Argument&&>: Passing PRValue ****/" << std::endl;
        check(std::forward<Argument&&>(Argument{}));
    }
}

#undef BLANKET
#undef CHECK_VIABILITY