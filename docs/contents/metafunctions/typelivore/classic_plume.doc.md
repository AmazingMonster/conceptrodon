<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ClassicPlume`

## Description

`Typelivore::ClassicPlume` accepts a list of elements.
Its first layer accepts a list of containers and returns a function such that when invoked, elements will be placed into containers via a process similar to pack expansion;
then, the type result of each packed container will be collected to invoke an operation.
Check out **Example** for more information.
<pre><code>   Element
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Container
-> Operation
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

## Type Signature

```Haskell
ClassicPlume ::   typename... 
               -> template<typename...> class...
               -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct ClassicPlume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

## Example

We will see three examples that present different use cases of `Typelivore::ClassicPlume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct ZeroStar { using type = Element; };

template<typename Element>
struct OneStar { using type = Element*; };

template<typename Element>
struct TwoStars { using type = Element**; };

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = ClassicPlume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = ClassicPlume<int, float, double>
::Road<OneStar>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = ClassicPlume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::ClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

[*Check out this test to see how it works.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgKykrgAyeAyYAHI%2BAEaYxBIaAGykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BXIF2mA5Zjc0EJZExcQnJCk0tbXmdtpODYcPlo1WJAJS2qF7EyOwcBJgsKQYHJgDMbgQAnimMrJgAdE/Y9GyCCufYJhoAghPEXgcAGo3AYFBlkMpcphvj8TAB2Ky/IEooEHI4nGEXdHHJinbE3O5sJ4PT5A5BghQkjwKNiOZAfM5fZGo/6AghA5TEVBEABKqCY6CBsNRwsRwpZopROMx50uh1x%2BMuhOYxKeZIpTHBQIA8rdiHisp8RVKUWzgQARTBNOgm00IpE/U2mrwZIxownCs4W3X6w0COXXW6qzAg9J0vAMuUvQ6MAiM7AgEBBx7qpnnR3OsUWjOwu1SmV4rHyjFFwMq%2B4kjWUkk/YDETCx97GyVS11hYBA/mCr0%2Bq022hyusNpvxqtMpMp3O/fOiwtK%2BfFlMh8fYcmU31xf0MFtO53t91yBh4btC84%2BvVb%2Bo7gnB%2B5h2nWyOMtwxt7xz6Twmr6d7lEInMzkdfNF0DBVZVvIlU1JJl1y1BQHwjUx01bc0OS5HlUFPOUaSQ3dRQdCU/wLcCy2xUiFwrNUYLXTVtUvA1r3w500KBfsmFtVsCMRWd9zdTsU17TdGKNSCQ0Qp9kNfV44wTL9bh/IDeP/eFAOArjUVA8jS0ou9qOreDa3rRt3wTZSgQPTtTyE9jbQuYcTNk1d5KxdTiLnCil088s9Oggz6L9JiUPc1FLKBI8TwFM9vWE7cfKgiT6WjGTmwnZNvzTL4lNbADfxA7ztMVJcqL82C6KpJ5cMkszWzC6zz05bk%2BSinDw2qxTgNUvLfi05VfKBN8413VjQXgyMoR8YtBsEXcHXynSvIW%2BKV0yuDwWpNr6Rq4jWIw5qe3zQjzN6k6StXNaEIYuLgqzVjbMHDSVMzLNQv4j1biEq6gr6hKqq25LR0/dKFMy38s1y7K4UetECpLIrlsrVbyqMkdTOYl03vqmL7qHYzRwqmiXO6kLpVh07fPO8rYqC5kSYst6Iqxi9AtEn7xL%2B58AffIGUw6w6ush%2Bb4cKiC2cRmiLo2x9/pu16Oy7KKhL2rCWouDmGT5mcBbc2EAHoACpDaN43db1o2ABVsCEc2jdN34DeNx27ahuEzDOMIKS8LAvTcNAGF2FIP2C2FyYS6aCGGggAWBAAtOJUH6YgxQsen5cEhrw4zbNidD8TM%2BC1idXCRPk9T9105i8P9aziG3Nz%2B989p1jzYAdwTyYEMIsKK59Kvq6A7PBZ6smztB35C5ZgMh5%2BXXdaBc3MAmIENDzX4wqELwUjSJR0F5RevFoDkGq%2B1mwgIUggTP/WL6v/usrcur98PoTRvBcboTlM/dyTbCLjj7lE4XyLpgQB8826J22j/VWbgT5T3vqvP4TR6QAH14JxAIBACY6AkwKHuKgl8e8FAH3PkCDeW90iYF3k/COTI1jE1nvPReHIuAIPXpvbelDCHEOQVwT6k8bxuCvhfKgtABQEGvkCdAWxoj0DvsTR%2BRDD48JfpSd%2Bk1P6CGEaIvEF8pFeBkViWmUDBRymAYnb%2BIBf4wP4caaeExDTIHwUoFomCCDYJALgtg%2BC5RcMPhfMhHCqGKJodgOh08GELyXmYVhb0AkUKCdwswfCryn00UCERYiJF6IMYbWxD9MbUOQUkhqr8IQTTYBokhGSdGSOkfQCxVj/7t2aEA4ukwL6t2acQSBljoGwJvPAmc48kGRiceg1x7jPGYG8RcXxJC4k7zmZ8MJFgOAbFoJwfwvA/DcF4KgTgbhrDWCBAoLYOxQzmDODwUgBBNBrI2AAaxAP4SQDwNCSC4PCM4Gh/AaDMIkRIZgAAcQL9CcEkLwFgCQNCkB2VoUg%2ByOC8AUCAGFtyOBaA2HAWAMBEAgC2AQFIXhz4UAgGgI4dA4gRHuJwVQQLEgAFpEiSCBMAZAyAgRSAeGYXglDCAkDwNgrgMhBAiDEOwKQIr5BKDUHc0guhhUtwNCkTgPB1mbO2XKxFOpiVEo5KgKgQI6WMuZay9lnLXlJIgB4Cl9Ak6XK4GsXg6LMWkAgEgclKRKVkFJZ671IBgBSDMHwOgBxumUGiHK6IYRmhXFVbwaNzBiBXB1NEbQPR0XXPJe%2BIutA40Yt4FgaIXhgBuDELQFFuzSBYBYIYYA4gC3VrwA2XoAA3RecrMCqB6MSvY1yz61DlbQPA0QDTJo8FgOVUc8BQqre24g0QKFWlrUYYdRg7kbBEUwYACgABqeBMAt0vDs65/BRWiHEJKs90qVDqEbQq/QdaUBHMsPoEdKLIAbFQIHLIlaGVYPPKYSw1gzDwtQPO4ggqO2fpqHULILgGDuE8O0PQIRFhlAqHobeRRsjIZmAUDI14hgYZWLBjNfR5jTA6GR3oDR5jEZGJUOYAwqN6HsS0BjyxKgbFOdsXYEh1UcC2bCrVnAjX0qZSytlHKuVWtwPy%2B1btHXOo3RsBAmBBSjAgI8kAkgzgPAAJxnHhJId5ZhJCJA0D8xIBmwUcAhaQKFVyHiJC4IkIFBmgVuZeZ0IzyQ4V7M4Mi1FNyN1utxe6/FuriXkEoH6u11K2CcGaCwVt8IGVMDgu6LgBmHhcDeby/ARBINCqlWKy90hr2KFvXK3QwalVMBVbswTwmAsIs4DqwlxKgQGqBCltLGWsudhy3lt5QJrWoFtXEYUbszBOtCwWrFHrJtertbFslK3/X9fS5qIwOWqghsPnEFFEBI2NsTbG%2BNpALvJtTemhwV3s1xlzfm%2BFRaS1ltoBWq7Na60Nre828j7bK3wq7T2g4V2B0bMbcO0dsaJ17HhdO2d1z52LqUMuv7HYwtbp3fuw9x6rvXvKxKyrshquyvvSAYNBh11AasK%2B2HH7tMIp/QIP9AHvT05A2BiDUHmc8dqOR5wEBXCseFWh0ojGsOFGvOLgjOHOOYeFd0WjDBE6tDw9R1X14NdK9I%2BxzXuRtf0fQ9Lx1mw%2BMSpa5qxtiK%2BvEFS%2BlzLu3hu5fyxocb8niszaufNl19zSDqc0/EFn0OHNOdy%2B8%2BE/gDPwi%2BZIczzLhVtcRcFtFYXsV4oJXq9b8WqU0o4Cl01LAFCto5a2kbmIJiFYU4KvQxOL2k6lRTu98LdBnFIA1praq7OtdExwTreqeuGuLyy0v5egSV9y9XjkE2puKbOGcf3mflsL7z5tu1IBy9b2QdP5Bs/UGO%2BZYdsNJ2zvwpu/m65V%2B7sZse5NnNDA81yve6W8tlbrm/dXYjwtgO20dqNpg7IC9qQ6CCDow4jpjpXAI5TqQYo68Bo5LqHBY7rqLZ8AGB44HpHrBhE6yAk4SBk6CCt61YgCd607GAvo2BM7wBfps4MCVq6xYLPrAaWCgZ7J85YAC40bXgIZIbG6oaIb65MbYZy5a4y6EZZDCFsZC5q4a7y464UYDDSEq6UbiGqHKFm5cYCaW7nI6HQ79525iZj5AgT4V5V5FhLwQDe4kC%2B7KYLaYpqYaZYCh6CYR7U65ZL7%2BC/IfJWZL7wjuYiZGFIq2AhYB5rA6aSD%2BCGb%2BBAr/IGaSBx7%2BFcDkGcBnC25gZBYOGB7Q48pBGZEhHhEbDzoZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/typelivore/classic_plume.hpp)
- [unit test](../../../../tests/unit/typelivore/classic_plume.test.hpp)
