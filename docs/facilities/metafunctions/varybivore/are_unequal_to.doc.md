<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreUnequalTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-unequal-to">To Index</a></p>

## Description

`Varybivore::AreUnequalTo` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are unequal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> != Target) && (V<sub>1</sub> != Target) && ... && (V<sub>n</sub> != Target)</code></pre>

## Type Signature

```Haskell
AreBoundedByOpenInterval ::   auto...
                           -> auto...
                           -> auto
```

## Structure

```C++
template<auto>
struct AreUnequalTo
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
template<auto...Args>
using Metafunction
= AreUnequalTo<1>
::Page<Args...>;

static_assert(! Metafunction<1, 1.0>::value);
static_assert(Metafunction<0, 2, 3>::value);
```

## Implementation

We will implement `AreUnequalTo` using only `<`, meaning <code>Variable != Target</code> is expressed as:

```C++
(Target < Variable) || (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreUnequalTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        { (...&&(Variables < Target || Target < Variables)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Variables < Target || Target < Variables)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQgZgAcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuTF5EANQAKi3AmATH2CYaAILjxF4OFy/EmHIRAEcvGIrqhni8TAB2KyvC5wi47PYHTDHU7nVAAOixADUWngmDF6ApHuD4Rd3p8CBdlMRUERlEw7qT4VCYS8yWTZo5kBc0AxxphVKliBczpcAG5iLwo2EcuGsi4QLEY8wBVUQXHEfGEzAKC6o663e76yFuKFuQ3EO5Ug2a7VEpZLE0AEWObLJUNdR3dLNlcMR%2ByYhxOYsxWJewF%2Bu0YBGJRyefouXkyRmpjMw%2BqOzuptPp6dREajbEECmVJO94OZ/t2geDaKIyrtBKJJMTXLwPL5AqFIpiqE8abuAH1xfrEwqlVjVeqmzq9QablbjebzZbrZmLbOHU7PW7K5CvWzwQB6ABU54vl%2BPJ4vV2wQiuF%2BvrzPl7fz4hrwDyNRoeVP2AOMExeZNwmAC4AFl7iYKgvAYBxskrLNvl%2Bf5MCBEEwROLhWxeEAQAZJkTgA0sp3jPdXnBdtkCHJgFCUVoIDAMBIOg2D4IaVEuFIC4uAxDRHnwyVvEwJYKLeZpuVo%2Bj4gICAoOadiEIEVENB4sweKOQSQGE6UxO9DgVloTgAFZeD8DgtFIVBODNSxrHJNYNgzcwjh4UgCE0QyVgAaxAEyzAxSEzEkJIkhMjQAE4Ao0AIkiOfROEkXgWAkDQ1IsqybI4XgFBANTPMswzSDgWAYEQEA1gIVJznISg0D2Oh4kiVgtlUJIAgAWgCSQLmAZAeSkDEzF4TB8CILV0D0fhBBEMR2CkGRBEUFR1CK0hdG4gB3YgmFSTgeCM0zzK86zOAAeXOGqqVQKgLnarqer6gbeMkYbFQ8Rr6BFVyuCWXhCq0FYICQBrUiasgKAgMGIZAYApA0mhaB2Yg8ogGJTpicIWgATwO3gseYYgcfOmJtEwBx8dIBriwIc6GFoPH1qwGIvGAU5aFoPLuF4LAWEMYBxGZvBfgQ8VdVOwUKfOLZ3PCHZjPW2g8BiXbiY8LBToILVUp50hxeIPslGdXYBeVowvJWKgDEA7E8EwLbztSRgqZm4RRHERa3ZWtRTs2/QBZQaxrH0FW8sgFZUFSBpuc68Z0GOZ1THsywzCyg3JoliPugphoXAYdxPA6PRQnCIZKhGbiiiyAQpj8KuMhrhh5mGBJuLsXPegmNoi/ydu6k7gQ%2BlaFuK7b2xu7rvRZhHsuFkrlYFCczYJCOjgzNITLeGy%2B6Ou63r%2BsGt6zEVXBCBIfUzDc/6PMtlYEEwJgsASCBfP8I4MUio5IUkDRJBCgI6UTIBEiolDgyVSCpTchiAIXA4qRSSHAkykguAmS/kELeZ0cq2HyrfIqwNyog0qldWqUMYbfRamwTgLQWDikhJ1JgvIDCpi4JFDEfErJjXPpNaasg5qe2kN7JQvt1q6A0jtPa%2BM14b0wdlS61VzgXFuqKYgtD6GMOQMw8CrD2H8Q%2BqgL68RL5HDMDfQGxUiHkPiHVaGBjwbfRADQuhnVNEC1YVwNSSMUZowxutQmuMqb%2BOJqTcmlM9Y0xjPTRmp0WZsw5lzKmfMzZbCsvgUWjhxbc04aoaWOwqbyzqKdZWqtcYaxSQDHWVMDZG0wCbfmRhzagHwXwG2Cg7YOydi7PWbt%2BELUEbIH2a0rJiIDhbZOVhLChxiOHV%2B1lo7ZFjvHRO4zrBp23hnPAWAZmLwHspPwEBXBT24qXcorc9DVwaEctIjcGij0WP3HoQ9J693rjnPZw8BhzzOe3Z5eRXkz0%2Bacseq9VjrBXn9MBMjTo7yceophAteJsI4afcaF9fpmLvqQB%2BT8RizMVhAqBbC/6QjQZCSERx/6BBQZvaFnBcq4PMQQ%2BARCqrXRsVY4glCtg0KeiwBQ4oeTih0cicYo1UU8O4j0j2fSlryGEUMnQIAEoSP2jzaRJ11pyJITdO6PLep8oFRcIVbCRVUggJ9exRjXJHAxc0yxdiIbsodQ4gVqRUgjlYUOU1tFVE9T4HQbxlBfFWSCUzdyoaQm5yphEwQUSmapMwKzdmYgEl6ySQ08ppA0md0yZLHJyAZb5MEIUpWKs1Y4zKVrSpetqkZFqabBpYFLYtMZG0%2B2jtnYWXclK%2BaEh%2BnLXlX7JVozjDB0mcU7ZcyY6cGPPHIOKcLBrOshsrZ8AdmPP2Ycl5JcC53Mrtc4o2QrkXOyHu8eHd3m/OLg8wejRu5nunlevuE85hfOBRCpeYKFrqppZqzgKiWC8v5YK4VQZdRmrPhNYxf0AaYuxc/Sga8CWJDYUcI4JkIooPSmhyEcVf1ZTpTggqmK/KSEhMNElXApCRWJV/LgkIwFHA1QR7BjK14jXw9vQjbH9bxEyM4SQQA)

## Links

- [source code](../../../../conceptrodon/varybivore/are_unequal_to.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_unequal_to.test.hpp)
