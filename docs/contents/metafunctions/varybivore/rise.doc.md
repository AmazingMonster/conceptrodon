<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Rise`

## Description

`Varybivore::Rise` accepts a list of variables and returns a function.
When invoked by an operation, the function sorts the variables in ascending order and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Operation
-> Operation&lt;V<sub>i<sub>0</sub></sub> &lt; V<sub>i<sub>1</sub></sub> &lt; ... &lt; V<sub>i<sub>n</sub></sub>&gt;</code></pre>

## Type Signature

```Haskell
Rise ::   auto...
       -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Rise
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will sort `2, 2, 1, 0` and use the result to instantiate `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2, 2>;

using Result = Rise<0, 1, 2, 2>::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Rise` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `arise`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, auto...Variables>
static consteval auto arise()
{    
    // `std::index_sequence<I...>` is created
    // for the length of `Variables...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        constexpr auto sorted = []()
        {
            std::array original {Variables...};
            // `original` will be reused for the result.
            std::ranges::sort(original);
            return original;
        }();
        // We use `std::type_identity` to avoid construct
        // an object of type `Operation<*>`.
        return std::type_identity<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<auto...Variables>
struct Rise
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (arise<Agreements..., Variables...>())::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJL%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnifYJhoAgjt7B5jHpy3ETDeBd4/PDH2XiOJzcYmAJEICBYt3uTzMu0Br3ebmQ43QWCosP%2BjwImBYqQMeNBeIJRMwoKY51QADo6bdDvsmAoFIcAPKpBJMBqkQ5Uoh0mkANRaeCYsXoCmxD1mjmQjIE40wADcxHzqXziHglBAlnCTAB2CyHE3HR6mw4AektxwAbBp0SAQBEsKoAPpKACOXkYm1BAElBbD7YdtYziJhuZh0HCLdbDvxiIcCAg3vQjCnDqgqHaNCKteLJUH7TTY6aIwR1gxjv4rP4ACKgzIAL0wboIgv9twgjudDFdHsw3t9FNOgfpvz15tNhqs04tJrQDCVqlSSf5qEOChIePQ73rNbr9d1ZYXxyNp7Ppt7n2%2BWa1wAiatn%2BbFEswCiDBsbgTnDyvC7xiY9qQo%2BzC0MBGiHAA7nQtCHPEhwRl4Sh7omyapkhH5eLQHaXgBvZfEYH5OturQQKBT60Hqv74VeFZVveeBgWIJx/gBhrHjR7FXvGADqbwoW8kG9gQVycm6eBYII1yQcmm5MMqqBSQqy4EMQXgOHRJrxoYWaxNomAOFmOZiZyuYclyDSgkGvyQaW84LgxxDVqJ4ltlJjCOGJoKWV81mnGRu40tyED%2Bkstl3L855WN%2BbGXpxPYEOgTosEwADWHn9pg7pej6gKjm4LaYNmgoQK%2BhYfjRdwXt%2B3H6nFtE4g8pKElGlLUoKFXvlKdmPOMGnGQAStqFL/BejmteSJL4m1xIfJ1E7YIyBgsoKDzABG%2BJeb1fz/qaKERMAhxDUwdD7ocWD7GZY37SaECikooIbVtbCCJ%2BdK8t1RZLbqSxOjd8XjT%2Bf5wpaABUkNQ9Dlpg1DAAq2BCPDUOw48EPQ5jaNPLis3TQtApLXCA2aQQ7Kcv52RAzjDyHUYhxCF4qRFNGQ3YbhF1%2BdyVOnBovJcLyZiC7CTU03Tx1swoOFkycB4jU9vP84Lwu/E6p10L5FPcwIIug/1zRym6zJKORvYKKwbbMqCkvS7yjPMxkrPswQtzcRwKy0Jw/i8H4HBaKQqCcG41jWFuawbMJCI8KQBCaO7KzpQEBo0rakgAJyBAatpR1wZhmAaBr6Jwki8CwEgaHzvv%2B4HHC8AoIB87Hfvu6QcCwDAiAgGsBCpOc5CUGgBJ0AkUQW5wqgABy2gAtKnhzAMg8pSDSZi8NGhCQilAv8IIIhiOwUgyIIigqOozekLoAvQV8qScDwHtez7ccB5wbLnL3ZPZock8z3PC9L5IFehwIAeCHvQJMOwuBLF4E3LQKwIBIEHqkYeZAKAQCQSgkAwApBCxoLhBI9cICxGfrEJ8xArh314KQ5g5C2QGSMk3aOg83oEDZAwWgFDz5YFiF4YAYJaC0HrtwXgWA0pGHEFwvAEYHB4GVCRc%2BOUjLnC2NHCIeJPbn0uLEL45CPBYGfupPAZdhGkDkcQWIjt6z4kMMAS4Rg44rCoAYYACghR4EwNBSyvto472EKIcQh9fEnzUM/S%2B%2BgbEoBDpYfQeBYj10gCsVAqQGhCOnuiWWphLDWDMNXMxWosDxN1N0Bh2QXD9imH4AWYQIhDEqCMAWRQsgCAqXoRpDR5jDESALOwJSBB9EmJ4DoegekyL6RMAYNSFj1NsOMlp3TxkdLqV0lY251ibAkA/Dg3tSBV14DXb%2BU9Z6SHnovQ4y8zDANwBvCBUdoExwcSsVMTAsCJCKYnSQgQaQZwNJIDQkgzCSHtBofwto05Fw4CXUgZdAhcBTlwW0E804T3hf4SQXB/AZ1tDs5%2BNc64N3uc3eBHcEFd3fn3NBGDwGjzYJwFoLBlQGmnkwFaNizlpxpLC/268iD5L0L4veATpBBKUCE8%2BughbXyYLfYRmztm7JfhwN%2BPdzgmU1PSxlzKmT0y4OyzlwDQHIPAccBEZg7mwJbiSylCR%2B7oNQGAkYdKGXTy1dgtOXA%2BZ4LxMQQhxDz7UJaJw6O/raH0IcJQ0gzCvJsI4c/bhvD%2BGCPDaImxEj/b4GkY4ORQiuWqCUXicNai6jPy0Toq4eitj%2B0McY6OZiLFKCsWI2xR0HF8Gca49xnjOTeN4Py/xB8hWyGCWff24rwn2MyVYaJWjCmJOSdkVJ6TAj1gndk3JCR8kkQScU0ZfgICuDmSEfsizFgNIyE0nIgz8inuKNkY90yRkNH6W0S9lTt2PoWZMzpwzZkvu/XMT9SyNmrDWQfWVT9z77MdRqll2rdU0ighAK5PLjUwrNQ80gTyXmUE2ZC6F7K/kGgxQXQI/zAVouxRBzgeLG4trbp3buH8bVWuINSrYdK54sAUMqeUyodU0nJOMNe%2BAeVST5bIAV/aj7yBFcOnQIBgiSulffcFcqcWvzJZ/HM7Hjmce44cXj7KBNkxAXaw1CQUOBDQ4S1uiDTMoKY3Z8BIBuPMzdAZt0RmjbEBYKnPgdAvU%2BpIWQwNVDgt0MMmGkxkbBDRs4WmzAPC%2BFiETSY5N4iK0iKkSUrNz9FHIGUQWwQRbNGxNLeWgxWpq28FrZY6x4jm3WacUwFxbiPFePDb2/eEgB3Hxk6E%2BTY7jBRJsNO%2BAs6UmcEtI6Fdlgcl7LyZ5Gdb7Sl7vKb%2BqpR6AMnrSGehoB62m3q2/euovTGg/ryK%2Bh9vQP3lC/fM/oB7ZitDvcs4DEcgMaNU5RjgaqONcZ43xozlzhMkBQ1AmB6HMMjCKRo3DIAzDssCIEfw/g/nuo0EjrOE8KPVyo7YfF5qlgJySGYGkyONDZ0zgiieBczACw0YEcDuPa4ErgZs1eOO9l48JysMxmRnCSCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/rise.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/rise.test.hpp)
