<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::All`

## Description

`Varybivore::All` accepts a list of variables. It returns true if all variables can be evaluated to `true` and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> bool(V<sub>0</sub>) && bool(V<sub>1</sub>) && ... && bool(V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
All :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct All
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto All_v
{RESULT};
```

## Examples

```C++
static_assert(All<1, 2, 3>::value);
static_assert(! All<0, 2, 3>::value);
static_assert(! All<nullptr, 2, 3>::value);
```

## Implementation

We will implement `All` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Variables
-> true && ... && Variables
-> (...((true && Variable<sub>0</sub>) && Variable<sub>1</sub>) && ...) && Variable<sub>Last</sub>
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<auto...Variables>
struct All
{
    static constexpr bool value
    { (...&&(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool All_v
{ (...&&(static_cast<bool>(Variables))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEgAcpAAOqAqETgwe3r7%2B0ilpjgIhYZEsMXFciXaYDhlCBEzEBFk%2BfgG2mPaFDPWNBMUR0bEJtg1NLTntCmP9oYNlw5UAlLaoXsTI7BwEmCxJBjsmAMxuTF5EAHRXAGqNeExR9ArH2CYaAILTxF4OANTvtFob3eJgA7FYPr8ob9pkxHMhfmgGNNMKoksRflFUJ5fgA3MReTDA6G/MEWX4QK4XcwANlpEFh8IA%2BqJpsc3FjPC8ILdiPdHpgFEthaTQQARY4QkHiyXA4E7PYHIknM6XG53B5PF7ApEotEYzm0f6Apm4uXgilU2n0xl4ZAsphsk6G7m8/lPYVLUUSo5S4EAegAVMGQ6H/QGQwAVbBCSMh8MfIOh5MJkEfW32x1KJoQAFAk5cUi/MxFo4vEAgfHeTBLWXphrMrOxAgQMBgY35twaIsl35lo7YCtVwm133AjNMps5tsd9kMLyApIEMjF0vlysEmuSjgrWicACsvD8HC0pFQnDc1msMLWG0wpLMRx4pAImh3KwA1iB92YLqCzJI8TxPuGgAJw/hoNLxEc%2BicJIvAsBIGjdsep7nhwvAKCA3avieO6kHAsAwIgIBrAQSTnOQlBoHsdCxOErBbKo8Q0gAtDSki/MAyAIlIFxmLwmD4EQfLoHo/CCCIYjsFIMiCIoKjqHhpC6IWADuxBMEknA8LuB5Hm%2BZ6cAA8ucFEEL8qBUL8zFsRxXE8b8fFmBSHi0fQGLmE%2BSy8LhWgrBASA0UkdFkBQEDBaFIDAFIJY0LQOzEFhEBRIZUShI0ACeOm8OlzDEJlxlRNoNS4c%2BNFsIIxkMLQ2XKVgUReMApyAlh3C8FgLCGMA4j1XgxClXguKCoZqI1OcWzPqEOx7sptB4FEmkFR4WCGcueCIe1pDDcQWJKGKuzdfNRhvisVAGMACjXHgmBqcZSSMDlcnCKI4iyRJ8hKGohmqfo3UoFelj6AtWGQCsqBLhkbWsdM6DHGKpiWNYZhoTtokjWDHRdBkLgMO4nitHowRzKU5R6Pk6QCBMfiFhT3QDKTixY4NAi9OMBM5IW1S1KzMwM0MFSjH01N6LCTT8wsFQrAot6bBIekcIepCobw6E2Sx7GcdxvGSPxFK4IQJAPt5vmnSsCCYEwWBxBAn7%2BEcFygUcoKSBokgATSyH7jSoGwRw8GkIhT4XDSXBQaB8Rh/ukhcPuTs0srhnoZh2EvqdBHEYFpFmZR4WRR5DFsJwjQsLioKsUwiIGEYTmgRcXAXKeQmG6J4myFJb3SB9CnfcpuglhpWk5QrSsq0ZHCmeR5yWdZJdlxXVfdbX9eN65qDubExtmD5ad4QFQXryFHlURFh9RXP5fINXMWgVw3bxYlyWpcpeVZU9r8FUVJUOE9FWMAQ1VaqGQak1FqtA2rPk6kdLYp58ADVqMNNqTdVDjR2E9aanRDLzUWllFaMDfJ8k2s%2BHae1MAHS6kYY6oA958AuldG6d0HrHmfB9DuMku6yB7kpU8/c/onURlYIG2DQa2zPJDAQ0NYbwwEcjVGsR0YiOlp0FmfgICuBFoWYmJQBbk1SJTTIHMabJD0fTEmOiubKJ5j0GYGjmZWLZrMbRktRY2MMS4voEsyZcGlrLGSI8DLKTVhfBeV8l5cDrg3DQ%2BthJGy8t402e9zaW2tpQBWAcg51zdqCOOoJQRHHdpIDihYx7J1sKnPy%2BFCIkTIuZE%2B%2Bd6KMWLsQFg9kWAKFxAiXE4SLhKmmIJGJrdCysNeuw56XCfogBgoPbS7V/GJ0CSZHOFkrK/BLq09pnTum9IshANyR9N5eSODvCp%2B8UBn2Pnnc5wwOlJCSKacJTJtmTmaRxPgdBH6UGfqeD%2BdVnw/K/qVX%2B69KoAJqnVWBmBGrNTEOAp6UDKH4NIHAwaiDRooOQBNdBghMFzQWktTKeC1qEKeiQ1IZDDqUNCNQ/ytCmCXWurde6j0trDOkhIDh8kvrcJ0JMvhxhAY2GEfAcG4jkScH9LDAGSNLAo1VmjPAWBFF2O6LjfG2QjFaPmF44xBQMi2LphkTxTNubdAcbYk1dQ%2BZmOcVzVx6r3Hi2tV4nx6w5beL9qPJOnBVkvM4m0jpeItlwkFDsg2IljbxN3v5JJVthiiNmukkAZg65HCOPuECMdkKptBFBeZaFOApxwmbUgX5JCgn4tkrgUhQJZKdlwUEfsjgBPzRhKN74/YCTzarAtbbhTbViGkZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/all.hpp)
- [unit test](../../../../tests/unit/varybivore/all.test.hpp)
