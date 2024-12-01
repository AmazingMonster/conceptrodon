<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Total`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-1">To Index</a></p>

## Description

`Omennivore::Total` accepts a packed vessel and returns the total number of its items.

<pre><code>   Vessel&lt;Items...&gt;
-> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Total
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct Total
{
    static constexpr size_t value {RESULT};
};

template<typename>
constexpr size_t Total_v {RESULT};
```

## Example

We will find the total number of elements contained in `Capsule<int, int*, int**, int**>`.

```C++
template<typename...>
struct Capsule;

static_assert(Total<Capsule<int, int*, int**, int**>>::value == 4);
```

## Implementation

We will implement the case where we count elements inside a packed container.

```C++
template<typename>
struct Total {};

template
<
    template<typename...> class Container,
    typename...Elements
>
struct Total<Container<Elements...>>
{ static constexpr size_t value = sizeof...(Elements); };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8XaYDmlCBEzEBBk%2Bfly2mPZ5DDV1BAVhkdFxtrX1jVktCsM9wX3FA2UAlLaoXsTI7BzmAMzByN5YANQmm27IE%2BhYVEfYJhoAgje3BJgsCQZPR24EAJ4JjKyYVweE2IXgc%2BwAKqharRDgB2KywgAiRysdweTxebwBaOOD32%2BP2GNeTHex2%2Bv2YbAAdDSrvtdkwFAp9h5BExpmQ8QTyX9qTTsPQ2IIFA9AXdgaCCBCoWIPqzahyPgLnowCAoaVTAZtrmj4fsJiS8Mh6QIJphVAliPq8AAvTAAfSlADcxF5MIdNojrXbUFQNRBlUK1fMUXDkZtUfc7gB6ABU8YTiaT0YecYTEMwE2ZiZTMaT%2BZzoruRKxHx5lMwGrFtwlYLcTASCi89BRRZrtUcyHtjKU9QgkOhcobTZbx2CBFI%2B3Hscn05nU8E8a12BAIBd3ndR3DXskIYjHEWtE4AFZeH4OFpSKhOG5rNZ9ctVpuzJseKQCJoD4sANYgY9mKlYTMSRYliY8NAATn/DQADZYk2fROEkXgWAkDQNFIc9L2vDheAUEAMI/C8D1IOBYBgRAQGWAgEi8CcKAgNAXjoaJQn%2BThVFiGCAFoYMkfZgGQY0pCpMxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1GI0hdBaAB3YgG04HhDxPM9PyvTgAHk6NoqVfX2TieL4gShP2ESzH2CAPGY%2BgrS2Lh5l4IitEWCAkCYhIWLIBiIqikBgCkMw%2BDoJ5iHwiAInMiJgjqL4jN4bLmGIL5LIibRKiIt8mKDSyGFoPKtKwCIvGAetaFofDuF4LAWEMYBxEavBiAqvAnUzczzUqOj1jfcc2nM2g8AiAzio8LBzIIaTUK60gxuICJkkwRFnj6xajE/RYqAMYAFAANTwTBdMsil8tU4RRHEFT5PkJQ1HMnT9D6lA70sfQlvwyBFlQBIOk67izi3UxLGsMxsL26SsAhiBFgqKpnAgVxRmaUhAmmIoSmyZJUgEInKdyNJenJuZWnaapJlp8Y2hGgQunqRn%2BlKIZug5oW%2BbJgWJBxx81klxCOFPTDzJwhyuN4/jBOEyRRM83BCBIQ4XwCoKLsWBBMCYLAYmx0hf0kTYqQgzZYUkDRJGAmD0OPGCILl5DSFQ18qRgrg4Ig2IQ%2BPSQuGPR2YMVrScLwgj3wu0iKLCqibLo8hKFi3y2LYTg6hYJ1YW4ph6QMIw3IgqkuCpS8JL1jG5NkRTPukb71L%2BrTdCS/TDK6kz5bMhOrKzuyqH2YvS/Lyu%2BpruuG887zIt8g3NjMQKU%2BI0LwtQHzohzxiD7XgYZ7LhkjC4CCuAwmhaFS9LMq0wrctet/itK8qHFe6rVVqvVcyTUWptQ6q9Hqp11iXnwMNKoY1OqN1UFNJ4r05pHi0otZauU1rQKCltV6e0DpKGOr1IwZ1QC7z4NdO6D0novR2t9duylO6yG7ppS8fdAbnSRlYUGWCsZQxhmkOGCNPS8JRmjaIGNxqQxZtzPwBMGDuE8E0fwyj%2BazEFjkam6RVFjESFTDomiKac1Zjzdm%2Bjia4w6LzKYhQJbjEsZkaxkwTFzClisGWAU5YKywrwZWF855X2AIveuGgdaSX1v5bewUvykDNhbAY1sMF%2BwDrXV2sIY6wlhJsN2kg%2BItH8RZXCthk5xNCunJA1FbLHzzqxdiHBi7ORYAoJ0xonQ3ypFiCY4koktxaEwj6LC3rsP%2BiABCA8Ej5WHn4pW48aJ0X2PZZp/FWntP2J02uPSpReVPlFDemxYmpwzvU6Kud9m%2BTXMgBICR7RbPtDs7sxAWB8WSo/aIz8so5WKh/H5JUyoVT/gfGqdUGowMwM1VqYhwE7UgeQvBpBYEjQQRNZByBppoMEPNTBS0VpfFwRtAhO0iGHVIadYIlCQrUKYDde6j1nqMFekMpSEhWFqV%2BhwnQEzuHGBBjYAR8AhGw04NGM4wNkaWFRgE9GMlZHWxsWkFwyiRakwcVoumuiRY6OMeLDVZiFF2JFoqix3R3GCwNCMKxehLX2JmKYzxT5ZYYLmWPDg08XktLaR0rpOzInNw3kbHeIVTbm0tpQYeaSQBmFrpsTYx5wJR3QnG2EcF47YU4EnQiJsbYgEkLCUSWSuBSAgpkx2XBYRy02KPDNpSKnDzEumgJmbg3xL2ikZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/total.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/total.test.hpp)
