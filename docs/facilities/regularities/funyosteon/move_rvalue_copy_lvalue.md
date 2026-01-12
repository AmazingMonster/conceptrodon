<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Funyosteon::move_rvalue_copy_lvalue`

<p style='text-align: right;'><a href="../../../facilities/regularities.md#funyosteon-move_rvalue_copy_lvalue">To Index</a></p>

## Description

`Funyosteon::move_rvalue_copy_lvalue` is a regular function.

When invoked by a lvalue, the function returns a copy of the argument. Otherwise, it forwards the argument similar to `std::forward`.

## Type Signature

## Structure

## Examples

- We will forward values of `Argument` of different value categories to the function `check` and inspect how the argument is constructed. 

```C++
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
inline void test_move_rvalue_copy_lvalue()
{
    Argument arg{};

    {
        std::cout << "/**** Passing LValue ****/" << std::endl;
        check(move_rvalue_copy_lvalue<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing XValue ****/" << std::endl;
        check(move_rvalue_copy_lvalue<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing PRValue ****/" << std::endl;
        check(move_rvalue_copy_lvalue<Argument>(Argument{}));
    }
}
```

- Now we will see how `std::forward` will behave.

```C++
inline void test_std_forword()
{
    Argument arg{};

    {
        std::cout << "/**** std::forward: Passing LValue ****/" << std::endl;
        check(std::forward<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward: Passing XValue ****/" << std::endl;
        check(std::forward<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward: Passing PRValue ****/" << std::endl;
        check(std::forward<Argument>(Argument{}));
    }
}
```

## Implementation

The implementation of `Funyosteon::move_rvalue_copy_lvalue` is similar to that of `std::forward`.

The difference is that when provided by an lvalue, instead of forwarding it based on the target type, `Funyosteon::move_rvalue_copy_lvalue` always returns a copy.

```C++
template<typename Target>
constexpr std::remove_cvref_t<Target> move_rvalue_copy_lvalue(std::remove_cvref_t<Target> const & arg)
{
    return static_cast<std::remove_cvref_t<Target>>(arg);
}

template<typename Target>
constexpr Target&& move_rvalue_copy_lvalue(std::remove_reference_t<Target>&& arg)
{
    return static_cast<Target&&>(arg);
}
```

## Links

- [Example](../../../code/facilities/regularities/funyosteon/move_rvalue_copy_lvalue/implementation.hpp)
- [Source code](../../../../conceptrodon/regularities/funyosteon/move_rvalue_copy_lvalue.hpp)
- [Unit test](../../../../tests/unit/regularities/funyosteon/move_rvalue_copy_lvalue.test.hpp)
