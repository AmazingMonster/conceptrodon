<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Carrier`

<p style='text-align: right;'><a href="../utilities.md#carrier">To Index</a></p>

## Description

`Carrier` accepts a list of sequences and returns a function.
When invoked by an operation, the function instantiates the operation with the sequences.

<pre><code>   Seqs...
-> Oper
-> Oper&lt;Seqs...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the sequences.

<pre><code>size() -> sizeof...(Sequences)</code></pre>

## Type Signature

```Haskell
Carrier
 :: template<auto...> class...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class...>
struct Carrier
{
    static constexpr auto size() -> size_t;

    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

- We will create a `Carrier` with sequences `Sequence_0, Sequence_1, Sequence_2, Sequence_3`.
Then, we will transport the sequences to `Operation`.

```C++
template<auto...>
struct Sequence_0;

template<auto...>
struct Sequence_1;

template<auto...>
struct Sequence_2;

template<auto...>
struct Sequence_3;

template<template<auto...> class...>
struct Operation;

using PackedCarrier = Carrier
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

using SupposedResult = Operation
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

using Result = PackedCarrier::Sail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Carrier`.

```C++
static_assert(PackedCarrier::size() == 4);
```

## Implementation

```C++
template<template<auto...> class...Sequences>
struct Carrier
{
    static constexpr size_t size()
    { return sizeof...(Sequences); }

    template<template<template<auto...> class...> class Stockroom>
    struct Detail { using type = Stockroom<Sequences...>; };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = Detail<Stockrooms...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfTC8RAAdKCbod9kwFApQcChJgAI5eRibBQ3J7jYheByHNwtYh4eJPEwAdisD0OlMOs0cyAhAnGmFUqWI1LwAC9MAB9AhszkQJZPKnHMmHYiYAjrBh8zCoKiwiDwpEozAKQUBCwigAixIpVJ%2B7yYn1OBr%2BX1NRv%2Bp0BILBAWwEIM0Nh4Mh0MOTVQyAA1sRUKgWOi9ZTMdjeVqJUw6CLNV5MkZDgQAJ6pTDHAJaj1EH1%2BgNfJXIhiol32k6a0k6jW6%2B7Ci3G76vQ31utWvFA1Alh1umF2rtOntw7O%2B/0sNGl4OHOPhYAeqO0dOZiPNOj5oe50edkAgZOpsvEkmV8mPB4AegAVBfL1fryenufL4cACrYISPoSHK%2B30/Xn%2Bf6s7PYDjTL40CLTBUgIMdbgeJ4WwBdtOwxAgsRxAsVS5DQ9xgh44OtBDeyQlDeTQsCuS4LDj2eRszTw21gSDe5Q1QxFC02LkzAo2DqMteC6IYpjiJY9CAk4nDuObcTWxtDte0dKEB345Cw0OAB5VNiCNbJRPue8L0OAAxPBiHGQ5sFUVh3jTP9sPuKcE2UJgfUwdx8UJVkTkzPFiAJIkYNOIUqRItiNFIY4JyC7kUjCmtAqE0izFCgLKQirkRL824qxsuyZyELxUiKZyACVVS8WheQ81T1M0gRiX88K4uCxL6uVUioqSj0Gu5BLouFFK0seUtMso7LDmKhRSvKjNDgcpyXO8tytyEOcvjU%2BJqoYdEhqQzTkC5eT4gICALi3BRWG5KEvjGibQty/KMiKkqypudUjzvK8OtA9BTPM34rMvL9KJpPBdv21oIBm71nK8nyEhATJ%2BSWBcKskF6ng4FZaE4ABWXg/A4LRSFQTg3GsaxqTWDZgLMAIeFIAhNHRlZvRALGNGBMwzAATgADg0Tmse5xIAkkMwSUkRJ9E4SReBYCQNBCvGCaJjheAUEAQvp/H0dIOBYBgRAQDWAhUiBchKDQN46HiSIzs4VRBYAWkSSRDmAZA6SkdneGcwgSDwdA9H4QQRDEdgpBkQRFBUdQtdIXQUgAdw01JOB4DHsdxhnCc4FSgRN3k5UOe3Eidl23Y9yR2cOCAPEt%2Bh3Oprgll4TWtBWCAkAt1IrbICgIC7nuQGAKQEpoMr4jViAYizmJwhaJNU94WfmGIJMVJibRMAcRfSAtthBBUhhaAX2OsBiLxgDxWhaDV7heCwFhDGAcRT6MrfHAAN1VLOmS3oEtlpuEF4mNY60DwDEDSq8PBYCzshPAss76kC/sQGI90IyPyMGAowDMVhUAMMABQAA1QkCdVp41pkHYQohxDh0oVHNQWd476CfigUmlh9DgLVpAFYqAILZFvg7C4HlTCWGsGYJWyCCRYC4QKbo79sguAYO4TwHQ9ChHCEMSoIwUhFCyAIKYfgdEZD0QweYwwEhjDqPIgQfRJgqPyJYnoNiJgDA0QsbRtgXEGL0LMVoZitEWJWAoCmmwJDpw4DjUgiteDKyLo7Z2rt3aHE9mYauuBfYNxps3OmOCVgIEwEwLACRZHM0CMCTmAQxYaBFuLeWWNEic0lhwaWpBZY02BMkRI3MeZcESFjSQXAsYVIltE7OKtbDqxyVrdu%2BsO6GzzqbPuA9642zYJwFoLAP4kgdkwOSCYuCc2BFwYEBMfZECkYHWQIcaHSDoUoBhsddAJSTkwFOd9wmRNGcrXOxsgSHELhsrZOy9kzgOUck51da7d3rscamZhsmt21nM5Z8Qzb9wDNCkYgLtmQiMAcrgIUx4vGMpQaesdl7zx3hS1e69N7b0QXvRgBBD7HyzmfC%2BV8b47wfk/F%2BBN8DigcHgL%2Bt9TmqD/i8HeQC6hZzARA%2Be0CtgEzgQg2myDUFKHQby6cOC%2BD4KISQshO9KHXLDrc2Q9CY4Eyecw7BIirDsLlTInhfCGScEEQQdAwi2EWHETEyR/tv7cLkUK5wEBXDeJSOo8o5i9C6IaJGtIxiGj%2BMWI46xjQvH2MMSGhotjXExoCT4rNeQc2%2BILZotNQSQlhw%2BZnWOsTsXAtxaCw5xyNBpPwOc2FWSW65NIPkwpIxZEgJaW0w51SSRDJJCSYWZhxYDKiVnZWqtJmIpmfAOZRt85opRcQVZWwNkJNHB/OkH8wV/HGN7LtfsA4pBNdQs1Ed5D3KtToEAQQXlvLTk0z5y6c4LILlQQ4R6XYnrPRey0Jka4Yp7j2gICLdXItg/XXdKGRinvylyc9nMuSXoIHtYgLBnZ8DoMSyeZKCbUpPrTajtL3470ZQfI%2BJ9%2BWYHPpfMQXLEE8swUq%2B%2Bb8hUip/uK5A/8pWCBlaA8BkCkyKtgQSVVvB1VoNeNq7B0y9VMAIcQzApDUzkN4A%2B0OEhzWR1fYwj9trjA%2Bo4TEZ1hNXUMFvieY69qxESPiFIoNsi7AZsUco0tailGpo8fG7IibwulDcbG9NobM39ETX5%2BL%2BbQsWM8Yl7Nxa5gxaLU3VY6xQn5ZAX%2BhtnAQNEePQoU9hwcPAnw52jJPam59umXkgpRTKDhLHSALmwIAgBCxqzAZ8sBski6Uusr4y1Ya37aUw5M6NAHOqVwAIfSSRmH6U0gI9alacFa23cJZhdsxP21Mw7SCJ4KMkEAA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/carrier.hpp)
