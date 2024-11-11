<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalPop`

## Description

`Typelivore::Pop` accepts a list of elements and pops the last one. The result is stored in `Capsule`.
<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>n-1</sub>, Element<sub>n</sub>
-> Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>n-1</sub></code></pre>

## Type Signature

```Haskell
TypicalPop :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPop
{
    using type = RESULT;
};
```

## Examples

We will pop the last element from `int, int*, int**, int**`.

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<int, int*, int**>;

using Result = TypicalPop<int, int*, int**, int**>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPop` using recursion over the number of parameters.

- **Base Case:** Pop the last element from a fixed-length list.
- **Recursive Case:**

  1. Preserve several elements from the beginning of the list.
  2. Invoke `TypicalPop` with the rest.
  3. Extend the front of the resulting list with the preserved elements.

Here is a simplified version of the implementation:

```C++
// We will use this function to
// concatenate the preserved and recursed parts.
template<typename>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...Beginnings>
    using Mold = Container<Beginnings..., Elements...>;
};

template<typename...>
struct Capsule;

template<typename...>
struct TypicalPop {};

template<typename First>
struct TypicalPop<First>
{
    using type = Capsule<>;
};

template<typename First, typename Second>
struct TypicalPop<First, Second>
{
    using type = Capsule<First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Mold<First, Second>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAdIADqgKhE4MHt6%2BeqnpjgLhkTEs8YmSAOy2mPaFDEIETMQE2T5%2BQTV1mY3NBMXRcQlJtk0tbblco30DpeUgVQCUtqhexMjsHOaBEcjeWADUJoFuXo60hACex9gmGgCCd/cA9M8HAOqYBwDudLQHXiUBwICDwCgOVC8DAcmWBqCerwOaGhTAIjFRXxBX2SxEwSmIADdMOgDoYSbjkGslCTkn0FAA6J5oljJAxo45uAiXZLotg3J4KAjELwOA7YVRohjoABixFkR0qVkqABFjlYHkzMCy2ZgOczWRi9dzeZh6WabkiDApwR5BEwIglSMDjcw2Gb6dh6GxBAp%2BQ9BcLReLJTK5YIObamg7iBzPVrGAQGebArcU08TIqngds8CtQb2ScuTzXaazRZMMAIgwIsBfWmHjmAekjAcALKeEnHZUHSP2yIxk7lysMatGJP0p1x72J938wLqx4qtXph76nVG4usUuM%2Bv3AMigg9pjJBReejLjWrvPrwsurez3f70UAFW5eFEtGUqGSCqVqvnK73Guhq3pubAHNKeDEIKfp7kKB4HK%2ByTvmIX7JBykHQQQsEZgujaAjWzo8kcgTdm4x6nueJxzguGb/rRV7aiBnJ3uBmGCk6RYmgcQiYMi6CwU%2Bh5IShn7fhhUEcTxfECAJu64VmOYES2XEkWRFFnrqJzsdhaYARqS76Y8jH5lpLFgV8OmcaxXy8fx1kWe6ADyWLQYJ8Evm%2BH5oRJWFOnZslOi5CAJOOOGZg2SnNsARG6pF2ZdmKEquLKsgbtxIneeJJzBaFD7YCAIBcbBjaFcBaJth2vlSQFUo0emhkMS8ABUrVte1zwIm1z7YEIz5tZ1DzPO1I3NYNxmPGYOzQvsXwcmcdBXDhJk3uZJr5QKHmHuRJ6aReE3KTFQheMk%2BTEgASniZ6HolO2UWZEQEE6j3Nc9gitfVl73IdByXZRN2kYhXmodlbiPW9BCvQcL1QzDNxlca%2B2bai74APpMNaCQEBAgroIVChbujdZuH913%2BSdZ3oKTtC6dgixqhwyy0Jw/i8H4HBaKQqCcG41jWAcCirOsc1TTwpAEJojPLAA1gEZj0pUZiSAAHMr/gaAAnP4ZgaAAbMrwTMxwki8CwEgaBopDs5z3McLwCggJbEsc4zpBwLAMCICAqwEMkZzkJQaAsnQCRRFunCqMrusALS65IBzAMgyAHFI9JmLwxKECQeB41M/CCCIYjsFIMiCIoKjqC7pC6FM3zEMenA8EzLNs5LXOcE5Zx%2B4eqBUAckcx3HCdJynkhpwcEAeMH9DEEcouLLwztaMsEBIEHyEzwHEDryHiTAFIZh8HQaLQZQsRt7EETNJcje8JfzDEJcTmxNofHO2LQfTk5DC0DfVdYLELwwByK0FoA7bgvAsAsEMMAcQ/8oJvzwEScBnNMCqD4mcTYYtHq1DbhcWI9dH4eCwG3IUeAzYQNIESYgsQ0iYGVFqGBFwjCS2WFQAwtYABqeBMDfCcsWW%2BpdhAfmLtIfO8glBqDbjXfQMCUB80sPoPAsQHaQGWN%2Beo4Do64y7KYSw1gda8FQNQ4gOc8TwGWHYRBzgICuAmH4KYYQHRzGGFMfIGQBD2LyGkDxDBZhDESFMKxMIBC9HGJ4doehgn1DCf0ZxASoljFaBEyY0wWj%2BLKK4yxQsNgSGbhwVmVs26237lHWO8dE7J1TmYCeuAs6z22FwBe4tWHLBCkwLAiQIAywWIEekGtAiVEkBoSQStdYW38LrDW%2BhOAm1IGbQIXB6S6y4PrDWytVn%2BEkFwfwAzdZFKrrbe2jsWkuxXp7Ve3su7%2BwoNvVA09Q7hw4M0FgBJKjRyYJaGBKcNb0iWag/ARBTG5yEYXcQJdxHlykVXXQh864Nwgfkwp1sjEd2uT3PuLy3kfK%2BS2Lgvz/kTynhvBIc9AhmGaUvV2lyd6b1ubS4YWL3l7BgfirglsaA01CmfC%2BV9H6CPvtfZ%2Br8HCCM/gmb%2Bv824AKASAsBgioFMM2JzfAFJHDILbmgjBaJBE4KNpzfBhDLjEOVYvUxFCxbUNoUoBh0CjDMNAGcvgHCFDcN4fwxggjxFgtEUIqFldOawtkSwvRVhFH4NUd0rmyRNGcG0QQOSypQ0GJtiYsxkbLG1GsX4WxUovGOKlBk%2BYbifH1HzaQdx9Qi2uK6Nm2J5bok9CSdWwJaTkk5AcW2lteSVhrFyU0mZBTW6HM4KSYgrz3mfJZXigl9INC1MBSQMlTTF6tNIO0zplB8lzIWb8kZlRdmVEqIEUZkg45TBRe3O2tgTlUvOfAS5Ptu5bwZcQMObBOAvKHiwBQBJk4EnxfSHUgoM6LuBXob1IiJBiNkP66RIBgjwuSLfJFw6bZot9mcA4vcx0sG/b%2B/9gHgOHknvcklDSpqBEpawt2a8yO7xffRmeIA/2nVRgBjWqNiPo3HXHI%2BXLT4QHPlXQV/LKGiafi/N%2BYr7lfx/n/FVmBAHALEPKyhir7WmtIKqxBGqq5aspDqyheq8HKKNSa0h5rBFWrobaphNYaPsKYFwnhfCBGUMg0XaDfrJEBp0Ah4NxgFE2AjRY6NsaODPFxvI/RlhDFczTVgDNtaQk5rsSkztTiSgJJLQUTI5bK2ZG7UErNqX60ZaiaVmJzb4mZNbYKPoDaavZbqz2wWfbi6oYOehjguH8N/oOBxoDGJBQLvqcu6jZy2mYA6cMKNRsd0gDML8wIgR/Dq22RbVblR9bddRdeh2Ts12yyqGnA9XApAa33QMrg1QjaBDQ/t1dU3B3pz21e57y9ljUPSM4SQQA)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/pop.hpp)
- [unit test](../../../../tests/unit/typelivore/typical_pop.test.hpp)
