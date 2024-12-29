<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreGreaterThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-greater-than">To Index</a></p>

## Description

`Varybivore::AreGreaterThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are greater than the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &gt; Target) && (V<sub>1</sub> &gt; Target) && ... && (V<sub>n</sub> &gt; Target)</code></pre>

## Type Signature

```Haskell
AreGreaterThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreGreaterThan
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
/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreGreaterThan<1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3>::value);
```

## Implementation

We will implement `AreGreaterThan` using only `<`, meaning <code>Variable > Target</code> is expressed as:

```C++
Target < Variable
```

Here's the entire implementation:

```C++
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
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgAMwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcTC8RFuABVWsBMAQodhgRNiF4HLdLsRMABxAnveIIhCGYEmAJWK63em3UHg0lQmFw1AAOi5ADVWngmDF6Ap0cCGbcsTiCLdlMRUERlEwUaKGdTaZcxWK5o5kLc0AwJphVGliLcYqhPLcAG5iLyYZUa26q24QLkc8wANg9ECRxBRUtZt15xH5gswCmWy0dAQAIlC1WLqbHEmr7Yywc8WdDYURXZdgASwYwCMLEhi6QyvFkjNLFZhHYlo9LZfLa6y8wXXsXXSLk1Ty/SmRnIVn2a6gyGhSL%2B%2BKWtrdQIDUaTWaLQqUQB9S2pp0urker0%2Bv31tyBvkCoURqNJlMxuN967/P6A357W7YVSsZ51r7Al%2BPs73i%2BtwALKokwVBeAwDg5J8AFXIOEJ2iOOZcviwAlmWlyVuEwAgWBEFQY0VINniBLEpgpLEOSlLQlwU6XCAIBrkhbhoQo3alneVy/kciJhlKP5XFqeDIOuTAKEobQQKBLQEdBAismYpC3IkymSOijHWt4mDLFxlzCaJ4mSQQEBgGAeGyZB8kMKyXDKUpKkaSAWm2rpyYcKstCcMkvB%2BBwWikKgnBuNY1jiusmx1uYiQ8KQBCaB5qwANYgMkkgchoAAcZhmAAnLlXDJFlmVcAEATSF5HCSLwLASBoGikH5AVBRwvAKCADXxf5HmkHAsAwIgIDrAQaRwuQlBoE8dDxJErDbKomXugAtO6ki3MAyA6lIHJmLwmD4EQwboHo/CCCIYjsFIMiCIoKjqN1pC6HZADuxBMGknA8J53m%2BQlgWcAA8nCo1SqgVC3Aty2retm23NtZjOh4U30Ca0VcMsvBdVoqwQEgk1pNNZAUBA%2BOEyAwBSEpNC0KCxDtRAMR/TE4StAAnp9vDM8wxCswDMTaJgDgc6Qk2dgDDC0OzD1YDEXjADCtC0O13C8FgLCGMA4jS3gBLQZaYZ/YagtwtssXhKClUBbQeAxG9PMeFgf0EMGtUq6Q%2BvEGaSjRmCGvW0YCWrFQBjodyeCYM9ANpIwwuncIojiFdce3Wof1PfoGsoKFlj6Db7WQKsqBpI0ytLRM6BQtGpiWNYZjNR7R0GwXPSC40LgMO4nidHooThMMVSjHZxTZAI0x%2BEPmQjwwCwjAkdl2K3fSTO0XcFPP9SLwI/RtDPA9z7Yy9j3ocw733iyD6sCgRVsEjfRwPmNX9LUQ4tK1rRtW3pQjEC4IQJCOmYGKGM4qB1WAgCiWAEgQGSv4RIHJcqJHKhoSQZhJDunqskd0uV9CcGqqQWqMUOTui4O6TKuUSrujSoVBB7pH4PRam1DqIDuo4wGrjIawMxrE1JijWabBOCtBYJaAIS0mC6gMNWLguUORcAyntA6JA8DHTsnHc6idpDJyUKnB6uglKvXehzO%2BD8mq8BakDEacJbhgxflDNayAJG4SkTIjKiNUDI3iAAxIZhgFYx6uwnh8RxokzcQTFGKAHFSK4A1amtN6aMwelzNmwtEk8z5gLIWbtRZFnFpLP6Ms5YKyVsLNWfttgBXwLrRw%2BtlYBSNsgE2wtzb1D%2BtbW2bMHZlMxi7YWHsvaYB9urIw/tQAsL4CHBQYcI5Rxjm7VRCdLoaNkCne6AVdEZwDtXKwOdWn52gYFYuORS7l0rps2u9d4iN12ZfDe1l26d3yOPYIHdd5LAniUHIR83lTxeYPFu1lt4rwecfG5jQAU/P3ifQF3d57L3BbfNYGwb7oxwffX69DOA2LfuIjWcNpGyI0M6X%2Bh1PHo0xqA0g4CmCQMoHfPBBDpHIICMkXKZVEgoLQZIOyJj/qtVsEw3xrD4DsOGiDIJATiB8O2II6GLAFCWh1JaJxiEJjyL/kdE6sg1ELOuvILRKydBJFIPoj6KsjFouaoDThoNwaqBlXKhVSrSQTFce41GgDEg%2BMDr1PGITCZit9WE%2BVaQ0ibikeuZVBB1y2o0XQWJlB4kBRSVLWKSa0mt2FlkwQOSpblMwLLeWYgiluxKUMzppAKmL2qYbVQxtQSNMEM0h6rS7asw6U7bpbtemZH6b7IZOEvXB0VBM8Okdo5%2BVinMi6EhFk3T1WnQ1Dis4122XneAhcDkLk4DscuS6tkWDrqYhuSim57IXrciArhPlPPQHCr5jQr3D0aLev5oLD6r0eWe198wz6z2Pm%2BoFMLv0VF/ciq%2BiLLpmroRajgEM7XyqtI60Ezqf4KLdUAslLCwEQNGHsyqdKQB5Q5IkFIRVOX1WIwEUhUHTGcEYZ1clKVJDJHgaVAI9VMqSAKlwbKZhaGVUSOamjvKBV312tRnlGHsarA9lkZwkggA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_greater_than/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_greater_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_greater_than.test.hpp)
