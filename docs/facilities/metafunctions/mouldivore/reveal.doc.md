<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-reveal">To Index</a></p>

## Description

`Mouldivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<typename...> class... 
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...> class>
struct Reveal
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
template<typename...>
struct Capsule;

template<typename...Args>
struct Operation
{ using type = Capsule<Args...>; };

using SupposedResult = Capsule<int, int*, int**, int**>;

template<typename...Args>
using Metafunction = Reveal<Operation>
::Mold<Args...>;

using Result = Metafunction<int, int*, int**, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Mouldivore::Reveal`:

```C++
template<template<typename...> class Operation>
struct Reveal
{
    template<typename...Elements>
    using Mold = Operation<Elements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7JoFuu/uHmMenAJ5pjKyYAHTPx9gA1MgGCgpvAPJ3xCYjVeJg0AEEJsQvA43gAlTAAN0wYlBYJMAHYrOC3ji3mcDkDLicCLd7mxno9sPQ2IIFCDsbivFkjG8ALKedBvY4AET%2BAKBOSuVL2jAICgprxAIBJd2OWLR6O5ctRqIA9AAqTVa7U61Vq7VvAAqmAmP21evBGp11q1FrR4PMgQiny8WC5JzQDC2aTF9PtYPxFyuMrJTxegWwqMh0IIbzcTDSCi89GVDvBgcJwdJzHJzzBxGAdIjUYIUJh/wSAoEKsxbyZEWAeNJ7t58cTyaJbnzhYlxcCFi5itT/vrLKEXjSxUw6HhSdosZ5cYTc87EQIpDea/VG63283gk1IP7KvTewJR2J2YeFO7Rcj4NHjdZmBaVC8XsaLbhiORtCuFcBYFi3BKV2VodArlvXtI2PNMwUfb85wXQJeWfV93wcQUTjXHcD1wghNXww8%2B3lEsBWQAB9JhvgSAgIAmdApQUB4qKLNxZ2Tdc3nHSdMmnDj51eZY5Q4VZaE4fxeD8DgtFIVBODcaxrDeBR1k2TAuTMQIeFIAhNFE1YAGsAkkR4NEkLh0UCDR/A0MwADZ7LMAAOZz9E4SReBYCQNA0UhpNk%2BSOF4BQQD8vSZNE0g4FgGBEBAdYCDSLx1woCA0H2OgEiiB5OFUZz7IAWnsyQ3mAZBkDeKRHjMXhp0IEg8EYrgZEEEQxHYKRWvkJQ1H00hdBagB3QE0k4HgxIkqT%2BqC34UuS2NUCoN58qKkqyoqqrTLMN4IA8TL6GITTtOWXgIq0VYICQDK0iysg0puu6QGAKQzD4OhdmIUKIFifrYgiVprnG3h/uYYhrl%2BWJtEwBxgdIDKaQIX4GFoIHItILBYi8YB41oWhQu4XgsBYQxgHEdH8GIGHHCRAnZMwVQYZS7YdLXep%2BtoPBYkBcGPCwfrSzwbzCdIJFiFiPjuT2UnOaMfTVioAxCwANTwTAhoraSdP4NrRHELqdZ6lR1HRwb9FJlAlMsfQudCyBVlQH0cgJwqGJ5UxLGsMxArF4gmpNeBVjsamchcBh3E8To9DCCJhiqUYWuKbIBGmPxE8yZOGAWEZEha4PMIEfopkjgo8/qEPC8mQZY8WBPbCr1O9DmNps/j3Og7UrYJEmjhJP8mbOBWgritK8rKuqnaIFwBqjsdLhTt0%2BXVgQZEsESCAjJASRAkeZJAnRSRzLMSR7N8/x7NScSOE80hvO0x57K4eznOSZyn/8Cz/D3%2Bz%2B/RoKQrCovSKl04pXQSvNFK5BKCPUOjlNgnBWgsAROiQqTAPgGBZFwZIjwuBmTqvgIgftmrdXavraQhtFDG36roN6I0EzAx7n3AKvBZoQMWstRByDUHoNJlVbBuCNC7X2rdQ6x0zAL3OlFMBMCEhQPSqgA6oxOEoM%2BKTLBXA/I0HnAkb6v10ag0BnDAx4NIbQ1hiLBGopkao36pjbGuN8Zw2JjLbYslKYh1pv1BmTNdhwzZlfWSnNuaAz5q4s6fthY6TFhLJQUsSZGFlqAYBfAlYKFVurTWcNDakM6uQ2QlC%2BqmySObOWHsrDWyCXbDecknYCBdm7FCZSvY%2BwSEQgO9segVz8BAVwjcWoxwqDnPQSdGh9PSBnRorclhl16JXAYYz86NCLtXQZbcm4NxLmneu8wa5DPnmsDYXd9lXyYQPDgbxlHcNUZg/hZldrT0IcdeeZ0l6kBXkwNelAe43zvtg8y6Iv7oispIY%2BJUWrMLkpwAB4V5bRVAUgRKC05EyOIHA7YiD1osAUAiSqCIsGPAuBMfBM8mp6GyXrXJ3UCkm1kroYIdCxqE0YdNP%2BnA5pJRSm8JaFziAsExdi3F%2BLCWxj2gokRCRjqBAkbC6RYq7rIrlYdEAOLJwUTxckCiwqqK8pKu9bRX1KB6NksYtGOkTWmOpnDSxghrFozcZgLGOMxCOJFs4hJYSMZ4CpphTx6NvHIGZn4wQ7N0ZBJ5tcUJAsIlw2iZLaWCSGywsVkwFWasNZ3C1rwclHUJB5MENS6hIBggYOMFbGwlTA41MaATVUDFLae0sN7Fhvt/ZVKDuXAu3TembOjuHKZdcRk5DGYOsouy1kzK6cshZHallV37bnbZxd8hbObisuO0yO6HM6sy3%2BgVB4YtKlinFbx1UEsJBMe5BCSBPOlcA5eq9RjVKvj8sYjxAiBH8LZCyvl33omfrulhULbCAMkcsTekh/C738M5ByyRJDJCsvvLgxbOCBBZXu4KQCLo91qgByFmHQOrDFlkZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/reveal.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/reveal.test.hpp)
