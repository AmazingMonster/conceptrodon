<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Funyosteon::copy_lvalue_to_prvalue_while_forward_others`

<p style='text-align: right;'><a href="../../../facilities/regularities.md#funyosteon-copy-lvalue-to-prvalue-while-forward-others">To Index</a></p>

## Description

`Funyosteon::copy_lvalue_to_prvalue_while_forward_others` is a regular function.

When provided by a non-reference type and invoked by an lvalue, the function returns a copy of the argument. Otherwise, it forwards the argument similar to `std::forward`.

## Type Signature

## Structure

## Examples

- We will forward values of `Argument` of different value categories to the function `check` and inspect how the argument is constructed. 

```C++
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
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument>: Passing LValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument>: Passing XValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument>: Passing PRValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument>(Argument{}));
    }

    std::cout << std::endl;

    /**** Argument& ****/

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&>: Passing LValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&>: Passing XValue ****/" << std::endl;
        BLANKET(check(copy_lvalue_to_prvalue_while_forward_others<Argument&>(std::move(arg))));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&>: Passing PRValue ****/" << std::endl;
        BLANKET(check(copy_lvalue_to_prvalue_while_forward_others<Argument&>(Argument{})));
    }

    std::cout << std::endl;

    /**** Argument&& ****/

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&&>: Passing LValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&&>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&&>: Passing XValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&&>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** copy_lvalue_to_prvalue_while_forward_others<Argument&&>: Passing PRValue ****/" << std::endl;
        check(copy_lvalue_to_prvalue_while_forward_others<Argument&&>(Argument{}));
    }
}

#undef BLANKET
#undef CHECK_VIABILITY
```

- Now we will see how `std::forward` will behave.

```C++
/**** Test ****/
#define CHECK_VIABILITY 0
#if CHECK_VIABILITY
#define BLANKET(...) __VA_ARGS__
#else
#define BLANKET(...)
#endif

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
```

## Implementation

```C++
template<typename Target>
constexpr decltype(auto) copy_lvalue_to_prvalue_while_forward_others(std::remove_reference_t<Target>& arg)
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

template<typename Target>
requires (not std::is_lvalue_reference_v<Target>)
constexpr decltype(auto) copy_lvalue_to_prvalue_while_forward_others(std::remove_reference_t<Target>&& arg)
{
    return static_cast<Target&&>(arg);
}
```

## Links

- [Example](../../../code/facilities/regularities/funyosteon/copy_lvalue_to_prvalue_while_forward_others/implementation.hpp)
- [Source code](../../../../conceptrodon/regularities/funyosteon/copy_lvalue_to_prvalue_while_forward_others.hpp)
- [Unit test](../../../../tests/unit/regularities/funyosteon/copy_lvalue_to_prvalue_while_forward_others.test.hpp)
