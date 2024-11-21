<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFind`

## Description

`Pagelivore::CognateFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
CognateFind ::   template<auto...> class...
              -> auto...
              -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct CognateFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto...Args>
using Metafunction = CognateFind<IsTwo>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

`Pagelivore::CognateFind` is implemented based on `Varybivore::Find`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct CognateFind
{
    template<auto...Variables>
    using Page 
    = Find<Variables...>
    ::template ProtoRail<Predicates...>;

    template<auto...Variables>
    static constexpr std::make_signed_t<size_t> Page_v
    {
        Find<Variables...>
        ::template Rail_v<Predicates...>
    };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSXADMpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwc5knhyN5YANQmSW4EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BAHoAFQwqFHABqrQuMTwADcSOwQAAxcLoI6wqEQ6Gwo79Nr42EQsEETAsVIGGmnNxMLxEAB0HNBHwmxC8DiOOIY6DBJgA7FYPkcpUcaXSGZgmbL6UxGWcWezOUlsEcDkwFAoOWzlMRMPhRDTnlqwdKjjy%2BQQjsbUEQAEqPWjW6Viiy2lqOZA6gQTTCqVLEI7q1BHVFiLy/b0AWi4YoAIqcfan0yLJdKlfLFbTlarmazUIaXjqDPrDe9gCbaYwCJbXjmpV5MkYjm66H8U47iM7UN2PWda/W2IIDZrXkkJZ9RWnZ9n3nmVQq1aWBXhiBMue87fzBcKzjidwQ997PVLV8Wb%2BuSxq2RXddWOcbTXhzZhm1ffbz%2BU6rrur%2B3peq2Nq%2Biqn6BgwwahuGkbRrG8bgTal6oRBUomP4Vj%2BCmEDLEcCYVoCIAgCwTAANa3JkwAROgdxMpkABetznlaGGYeh7yYbx0p4FQMFwWGRxQOWZgAGzmBJ75mmulpuKeu5amRMbeJgyzLL%2BfFoeKRwmgQGwMEcGjpicC7LjpvH1Eo2lWeZPoGUZRHJrO5lppxEGpgRdlYRZS7gZmAXgjxuaFvmZx3kykbllqlZ6lObJjpgDaTnuNrtuEwBdu6vb9oOw5MslqVNrFM5zkFFUfFFG5EFuZ6kBGm5CJgaBCo1MUcgA8gQCDxD%2B3L3PaW5CkySkEI1LVtegjU9X1O5lSK4q/jV5zhWu0WlmV8WvkaJpyRa6XSgeDqAUOwGBXpWGeXM/pCTS8FNXValxicnncfZJw4dh%2BGEcRcWkeRVE0XgdGmoxZwsWxR1WR9n38YJbXCcQvk6WJnKSdJsmfvJY3bsp2Cqchmmo3xoFOcQxmmW5mYfKT1m0EoRwCfdIZhvTmHo0%2BmOSdjX4KVNAjHoTIAvRpWmeWTekU8ZrkZhZdOSwzTMs0jD3s0rnMczpR5MnN/WLZrOlkXe%2BVAXQTJ8/JhuhfDEFE%2BpRxgGApx9km2s2hLtvw6BHu8TLRxmCclgjcebj6wt05%2B5hJvrTSZvnRbZxWxaNt2zHovIWZ0fuZZ6c2QqRu6Y5mCGZTLnZwr3tS79qOVSB/lVd7q2rZ1T5xS%2BiXFROTYw0cmWdsOeVnYVo51ilPeJaCwX15CBIIkiKLoiaZFHhSMJEvP2BCuvhLLsSMJHB4dFrmvBKbySZIOuf1Jx/erdbdOO2JSn357idR%2BoCfNK63Ty3gQ/R8iJiB4CYDEegA1vYD2ysoJgwAULe1dqHJkwDQHgO/GnaUsc5RrgTqPNwr8p5WhngAu%2Bm0gGtDQRAvut1oJqzZuGQGFFqI3FovRCGbgoYQ21LA%2BBNxUQNznHxXWZxUFgIgZgjOpthz8MtvtHGqco6XUXBVRuYID5wmPswH%2BuJd4X0PtvPEN9FbvA0QScxG91HzwACrfibHoqxFinF7xMV8BgBwvDHCZG1LYqRe4cRCoAqMABJd%2BQ1%2BTBIUNYgA7qgMEIAjipC8OA6CgMYioE8DcNWhh2JuGCb2JBZgKyXjUSYoJNZiDAEgdAo4ABZUuTAqBeHcY0PKWjT64iZJEmJcSAlkV4fed4lSiHlWXLQ5ANwErxAIBAepLQmktOyEyDQjUgiB0akkF4DtXqu0KVpYK4zJn6mmbMhpCyHBLLOCso4azNkqUzo7XZSQ3ZcH2XODgqxaCcH8LwPwHAtCkFQJwNw1hrC2nWJseMZgkg8FIAQTQHzViUQCJINkGhJBcFFEkDQ/gNCSQkmYAAHIS/QnBJC8BYBIDQKy/kAqBRwXgCgQArPhf8j5pA4CwBgIgEA6wCBJImhQCAaA6R0HiJEVg2xVCEokgmCSkgjjAGQAGKQbIzC8A/EQEB6A9D8EECIMQ7ApAyEEIoFQ6g2WkF0EEaJDxUicB4J875vyEWAs4F1VkAqjioEEtK2V8rFXKpuaioOEAPCivoOGXYrzeCsq0KsCASARWpDFWQIVybU0gGAFIMwfA6A0h3JQGIrqUTMGIBcB1vBS1Ii6jEbQrVWWwpFT3LqDBaAVstVgGIXhgDMloIzStpAsAUSMOITt24G1om/K6kMrVWTbFheEGkXzLW0DwDEB45aPBYFdfcPAlLuC8FRPEdJSgUy0kMMANdRgEWrCoAYKp8I8CYGiV1a4fzYV6uEKIcQxqv1mrUK661%2BhL0oFBZYfQ66mWQFWKgPx2QmUcATICV2phLDWDMHS49xBtXTpgz0SdzgICuGmH4IIoRwjDEqKMQoGQsgCFI3oIo9GGALBGNUAjFyBBX0Y0EOwhGmiTEGJRxYNHbBCd4%2BJ%2BYIn2MSFWAoCFWw5Oko4D80gtLeD0qOH6uVCqlUqpDaJXAhASDBxhcsWNt7Vh9SYFgBIBFSDIskEkNkABOJIopJDorMJICS1L/ASVcyp8lpBKUwrZBJLgElCWucJVF/wGL/DuYkup119LGXMrhbejl3LE28s9aycglAM2RolWwTgrQWColFAmJg8VOxcFc2yLgaKNX4C1XgHVQQv0Gt/dIf9ShAOWt0Lm21TB7WHqdapl1lr6Uev5ayb1glKvVdq/V7KjXmtotEuGlNkazNmAs1ltlCak2oAjfEIrwrzt7dGCtmruojCNa4CsmgtAC1MogMWy11by2Dt%2BxcWt9aHCDubY2Vt7bXVdp7X2gdh6h0XtHdsAF%2BATQXOPYhgFs7kDzsHUu%2Borq10bqRNu5HsaQEHthdh09mBz0jqvVlbL964EKCfS%2Bt9jBB09Z/Ua/rsgAMWoBSNkDN60NWAg0T6DDm4ONEQ8hggx4Uxi4w1h%2BIuGpfyfqAJlwQpJMUfKLJ2jxRsiSeY40Nj1GOP8a44JgYknreNCvhbpYfGJOeE6HoOYbRnc0fk4po1U21MabdRwCMxAqs1bq49jbTWWsaCM%2B10z0ajtxsRaQGzdnKBTZC2Fpr6LRRJdFFiyQPn5VBGD%2Bl2wmXU8Jty0gPlAqrslfFZKir4eA0sAUKiAMqJNvygmG1kz2rdWyF67zk18hBuC50CAFIY2JuOpU0HtL7qCsOh9WHlgHeu8977/JB0YabuprM0kFP2W8vN7TcVo/kbRbIFSKkfhjWbj94IJM9v/X839SLSW8ISJ/t/7lpA4Nqg7nYtptodoo6YDdq9piBw6wrDqXpjoo4Tro7TqWrY647w744roApE6boXCk67oU6DrU4ZC06I4M43onZ8APqs7Pqvrvpc6j484SB86mpT5Aaz4i7GDgY2CS7wCwbwZBicAQikTK6WCYaabYbq6CGcaNA67uDu75DkZCg%2B4cZm4m7KFkZpB0bm4yaW6e5a4248baFGG9DcZCbqGe5u55A6Fe7CYG6GGvJrAbBKYuErrL6zacCb7b7d7Rh74WgH7GZapmYxrHbxrWaYC2ajAOYro54gBmBNZJBJD%2BC4oYrUopGijRapbeEMpV4spWaOYgCSD%2BBub%2BCEqSSuaSCuZYoea1ArpJAzZ0qcCWYnZTbqq5EtH5E16rDYaZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_find.test.hpp)
