<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Conceptrodon

A C++20 metaprogramming library focusing on metafunction composition.

## Prologue

Both `boost::mp11` and `kvasir::mpl` contain a metafunction called 'compose.'
It takes in a list of templates and a list of initiators.
The function instantiates the first template and uses the result to instantiate the second one, then uses the result to instantiate the third one, and so on.
Namely, `mp_compose<F1, F2, …​, Fn>::fn<T…​>` is `Fn<…​F2<F1<T…​>>…​>`.

However, since we don't have a universal template parameter representation in the language, the template heads of the parameters must be specified.
Regarding **boost::mp11** and **kvasir::mpl**, `F1, F2, …​, Fn` must be templates that accept only type arguments, meaning the universal template head of `F1, F2, …​, Fn` is `template<typename...>`.
Therefore, many metafunctions in both libraries are not composable.

Conceptrodon restricts the template heads of metafunctions to be 'conformed' so that mixed 'primary signatures' are not allowed in the metafunctions' parameter lists.
In the following example, the template `UnconformedMetafunction` is not permitted since its parameter list contains different 'primary signatures':
`type`, `auto`, `template<typename...>`, and `template<auto...>`.

```C++
template<typename, auto, template<typename...> class, typename<auto...> class>
struct UnconformedMetafunction {};
```

To make `UnconformedMetafunction` conformed, we deploy member templates to accept each kind of parameter.

```C++
template<typename...>
struct ConformedMetafunction
{
    template<auto...>
    struct ProtoPage
    {
        template<template<typename...> class...>
        struct ProtoRoad
        {
            template<template<auto...> class...>
            struct ProtoRail
            { static constexpr bool value {true}; };

            template<template<auto...> class...Sequences>
            using Rail = ProtoRail<Sequences...>;
        };

        template<template<typename...> class...Containers>
        using Road = ProtoRoad<Containers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[The reason for the complexity is explained here.](./docs/introduction/hello_world.md#implementation)

Overall, this library utilizes member templates to take arguments with different template heads in steps, allowing metafunctions to be composed naively.

For example, since every member template with the template-head `template<typename...>` is named `Page` and every member template with the template-head `template<template<typename...> class...>` is named `Rail`, every `Page` can be accepted by every `Rail` syntax-wise.

```C++
static_assert
(
    ConformedMetafunction<>::Page<>::Road<>::Rail
    <
        ConformedMetafunction<>::Page
    >
    ::value
);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAEArKQADqgKhE4MHt6%2BASlpGQKh4VEssfH%2BSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7BwA9ABUO1sA1B4M/MRs6ACymA1UXgydDHu7WxsmGgCCBJgsyQYfJv5uBAAnslGKxMAA6SF/bAvV4KAjELwOA4CY6nC5XG53WEmADsVjeeyJew%2BXx%2BmD%2BbiYXiIkPB0NhxL28MRyOUxFQRGUTGAFMJxLxBNeTKZpO%2BTF%2B/zF5MpQJBzDYdOhe2QBgUCiV/hh/JFzIRSIIe3ZnNQACVUEx0IzdXtBdabcTpRKKVLPuLJVSaahNdgVWqNVCtfaHXrWYbjURTUw6MGHYK9RK8MgVQJ4ZhVMliHtoqhPHsAG5iLyYW34/UU3EAET%2BFlL1f8QtjNqdHpbLs9tMDvtVTHVdKEmAAjsXbpgFAydSGvOkjHso3Rbf5K0aOZHo7RKQPh4w1gH6UGG02iXj643J6K3TLXWTnbLgaDFV2/b294cGtNiOOg%2BfidOwsA5wtdBF2XCMzSAyk32jcJPx9GtgxPeC3mDNtKWpTtwQANUaPAmGiegv21YVfxnADuV5ECVxNcj22w4hcPwsc4MPZCqyQ15YW2XY9gAFTHQ1HmeN54UTZAAH0XziAhYQgYNDjRTBzkuJhrluRwBEpaEQBAGjNK1bTzUtPTsAM9cEP%2BI8USOEh0WU1TsQs/SdJ5PliOPb83L2bTC28Vz5hrDhFloTgEl4PwOC0UhUE4NxrGsZlllWEtzH8HhSAITRAsWABrEAEkkcENAADjMMwAE4yq4BJiqKrhcVxaRgo4SReBYCQNA0Uhwsi6KOF4BQQE6jKIsC0g4FgGBEBAZYCGSGlyEoNAvjoOIIjBThVCKgA2ABaLbJD2YBkGTKRwTMXhFMIEg8HQPR%2BEEEQxHYKQZEERQVHUEbSF0LhSAAd2IJhkk4HggpCsLMqizgAHkaTmw1UCoPZNt2/bDuOvZTrMPYIA8Zb6CzFKuHmXhhq0RYICQJbkhWsgKAganaZAYApDMPg6A%2BT9KGiSHojCRpARB3g%2BeYYhAWh6JtBqYa0qWthBGhhhaEFr6sGiLxgCpWhaAG7heCwFhDGAcRVbwYhpbwfMx0h9MahpdY0rCD4msi2g8GiQGxY8LBIYRPA2r10greIHMlErT4jbdoxMsWKgDGABRMLwTA/uh%2BUhde4RRHEF77vkJQ1Ehn79CNlA4ssfR3YGyBFlQZJ1IYXWdvhK0l1MSxrDMHrg/orBq4gRYOgblwGHcTxWj0EJplKco9FSdIG7GPxfvnwoGD6GfBl%2Boe6kmJe9B3rpJg3gZ4m3vfx9yc%2BehP2Yz8HxK1gkMGOFCrrId65Htr2g6jpOgrsYQFwFdQmZhUok3SjHRYCBMCWkGAPUguVJD%2BHBGVfwDUNCSDMJILaHUEhbTKvoTgLVSBtVSuCLaXAtpFTKrVLa%2BUqpoK2u/L6vV%2BqDUgSNCmk1KbTThvNemjMCZrTYJwRoLB8y4h2kwZ8s4uBlXBFwQqF18BEF7ndWQj0c7SDzu9QuX1dBswBkDIWL837dV4L1WGs0aR7ERl/VGB0exyIUUojQOM8Y0wJraMBZgIFk1GrwoRcQFoM1QPjQYziWaVU6jQWgnMBoQB5l9EWAsM6pLFhLKWDgM5y0YAQRWytIZqw1lrHWGcDaR3WJFfA5tahW11pFW2yB7YZydpgF2vA3YewFt7appN6IBzSsHUOmBw6GyMFHUAXC%2BDx0TsnVO6dA55y0c9HRsg9GfUioYku0d25WArt0/utd66ZCbi3P4lZ9md27nEXu1sa62A6RbZwEBXD71%2BlPEop854FEXpfZe%2BQF6ZFvrPbezy7jdFGACg%2BEKG5QqmN8u%2BB8L45EBSJJooKt4PxWE/YmRDX4Q1YZwBxP9ZEAXkYowqONgFqJ8eA0mUDSAwLgfEBBTUSFkIUZg3ECQyr1X8FgnBkhfoWKhn1WwHCAncPgLwma8NQnBOICI9Y4i0YsAUPmZM%2BZKXknhCokBN0NEPWzmszOmyi55GMcDPWZiiU9RhvwhGSNVDqs1dq3Vzp4QePCV4uI9L/D%2BJjmNKmvraaKrDQTEAWrkjJDEjqsqYk9UEDEq6nRHM4iJOSZFDJKs0q5qydLXJ4T5YFKVirGpmB1aazEOUwOlTJn9NILUi2DSbaqDth8NpggOmQ26Z7QEfTfaDIziMtIYyI6TP/MGuOPJ5kpzTowDOKzTUSHWW9AuWydB5AMHs8uNgjnwBOQ3XWGwW5lw7pYLulie43QeQgw%2Bfg3mjw%2BUEUeWKz5ArXq%2B1eDcP2wvsPC1FE9wWAd3jfaePzr7QrRSiiDSKwU4qSs/Al5iP4krTXsDVWqCyeo%2BN6oBqiSD0uJoyrh0DYFYDZS/TlIByrgn8JUaqIqOqMdxNQlhDqJUDSGkypBCRUF1VxB1IqkhKpcBKmYZhTV/D2ssZwMj5MX7nU4/JiV0rFjB3SM4SQQA%3D)

## Structure

Metafunctions in this library are categorized by their template heads. Thus, the source file of every function is placed based on such categorization. For example, to include a metafunction `VeryFunny` of template head `template<typename...>`, the include path shall be `"conceptrodon/typelivore/very_funny.hpp"`. The following tables show the template heads of the metafunctions contained in each namespace/directory.

<table>
  <thead>
    <tr>
      <th>Namespace</th>
      <th>Template Head</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Typelivore</code></td>
      <td><code>template&lt;typename...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Varybivore</code></td>
      <td><code>template&lt;auto...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Mouldivore</code></td>
      <td><code>template&lt;template&lt;typename...&gt; class...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Pagelivore</code></td>
      <td><code>template&lt;template&lt;auto...&gt; class...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Roadrivore</code></td>
      <td><code>template&lt;template&lt;template&lt;typename...&gt; class...&gt; class...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Raillivore</code></td>
      <td><code>template&lt;template&lt;template&lt;auto...&gt; class...&gt; class...&gt;</code></td>
    </tr>
  </tbody>
</table>

In addition to these namespaces, a couple more are introduced to contain functions whose parameters are of the form `Vessel<Items...>`.

<table>
  <thead>
    <tr>
      <th>Namespace</th>
      <th>Template Head of <code>Vessel</code></th>
      <th>Primary Signature of <code>Items</code></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Cotanivore</code></td>
      <td><code>template&lt;typename...&gt;</code></td>
      <td><code>typename</code></td>
    </tr>
    <tr>
      <td><code>Sequnivore</code></td>
      <td><code>template&lt;auto...&gt;</code></td>
      <td><code>auto</code></td>
    </tr>
    <tr>
      <td><code>Warehivore</code></td>
      <td><code>template&lt;template&lt;typename...&gt; class...&gt;</code></td>
      <td><code>template&lt;typename...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Stockivore</code></td>
      <td><code>template&lt;template&lt;auto...&gt; class...&gt;</code></td>
      <td><code>template&lt;auto...&gt;</code></td>
    </tr>
  </tbody>
</table>

General-purpose functions that do not fit any previously mentioned namespaces are kept in `Omennivore`.

<table>
  <thead>
    <tr>
      <th>Namespace</th>
      <th>Content</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Omennivore</code></td>
      <td>General-purpose functions</td>
    </tr>
  </tbody>
</table>

Finally, ordinary-function-related metafunctions are kept in the namespace `Functivore`.
These metafunctions are created to inspect and simplify ordinary functions' signatures.

<table>
  <thead>
    <tr>
      <th>Namespace</th>
      <th>Content</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Functivore</code></td>
      <td>ordinary-function-related metafunctions</td>
    </tr>
  </tbody>
</table>

## Example

In the following example, we will make a metafunction called `MakeMap` that:

1. Takes in a list of type arguments and extends it by void*, void**;
2. Passes the extended list to `MakeFunctionAlias` to create a function signature that returns `void`;
3. Instantiates `std::function` with the resulting signature;
4. Instantiates `std::map` with `size_t` as the `key_type` and the instantiated `std::function` as the `mapped_type`.

We will use `Mouldivore::Trip` to compose the necessary metafunctions. Check out [its documentation](./docs/facilities/metafunctions/mouldivore/trip.doc.md) for more details.

```C++
namespace Conceptrodon {
namespace Mouldivore {

template<typename...Elements>
using MakeFunction = void(Elements...);

using SupposedMap = std::map<size_t, std::function<void(int, int*, void*, void**)>>;

template<typename...Elements>
using MakeMap = 
    Trip<BindBack<MakeFunction>::Mold<void*, void**>::Mold>
    ::Road<std::function>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Commit
    ::Mold<Elements...>;

static_assert(std::same_as<MakeMap<int, int*>, SupposedMap>);

}}
```

We can use `MakeMap` again in the composition.

```C++
namespace Conceptrodon {
namespace Mouldivore {

using SupposedNestedMap 
= std::map<size_t, std::map<size_t, std::function<void(int, int*, void*, void**)>>>;

template<typename...Elements>
using MakeNestedMap =
    Trip<MakeMap>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Commit
    ::Mold<Elements...>;

static_assert(std::same_as<MakeNestedMap<int, int*>, SupposedNestedMap>);

}}
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBJcXKQADqgKhE4MHt6%2BASlpGQKh4VEssfGJSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxCVUNTS257SO9Yf1lg5UAlLaoXsTI7BwA9ABUO7t7%2B1sbJhoAgtu7ANRCy6uYF3tHp%2BcHL4fHJ%2B/MbArJTGsXHgYa2SBGIGAEFxMAHYrKcvpgfn87gBZZa0fAANxId2hsI%2BTz2FwsYXQFj%2BAGt7rtHicCJgWMkDHSTP43HSGUzMCy2QBPZKMViYAB0IpZ2AuyAMCgUFwA8vziExHAIxe8FKCvA4iSSychye9ce8LsaLuzGUquayCHyBWwRULsAx8EYFKrTiaLuriJqCBdlGCiKj0UaTYb3R6TWbOdzrfz4fbsPQ2IJXf5sCGIxcvOkjBcg%2BhIf4ACJyhVKzLcxP0xgEBT20gXR3O4B10Vpll4j3Qosdg3h41Ri0xm3xkVNsItt0nD3Zid5zwFlkl/2oQMLytOietoWq/x47u907vZ5bbVOgBiYMEVJ2NMHzKt9PND95ccF9rFEqlMvlcXLKvbU4vR9M90EvWQDRhDNTSfaMrRHd8RQsTBgDCBgtynD1gK1Fc12DftISggiPXvS1X1tYUxyTGtU3TYiTVnXN80LEtf0VZUGG5ZDUIYdCXXrRtqJTD92z3aCDzEo8CNI4c3ztJCULQjDAOnBic2Aed0RYv0A1QfMuMU3itxE9NJI%2BKEezM49CQAFWIPBkhvN5Thkx8OSHeC5Monc0y/JhpQuAAlJh8FQKdsN9OyHMgzsTRPC4i0wGhwiC1AQqcmkSNgjy2Wyl9Ywoky/ICtxGkwk0Ip01dUECtL0HEojVIjeKPBYFhCGTX0HmgiqNS1Vr2oIHrjTDJrM2NFqBG0FZ/wYDLhojVzyNHIUhDwYBmFoWiFpndTNMXYsATK1lgtC7k1o2sRt13UzYojCT93oi5JsEMIvFm%2BanqW76EPknzxUlfztxOYBiEwasU3KiNGI02r0qXC4ouSbkBsIEAQFI/axXRzHcJquruRBsGIdrEzDzGh6%2BzG768rIgqVs/QHpXtInwc67aCJh1L4cOvG4fq1lWZJ67RP3Czycgntxaks5Xjlg4aXi888GIdVG1UVhGTubqCXlvXnPxD4zH8MJJS8LBCzcFgmGRlTzBNoFvAt7kqC8IEOLEKdPkFRF/kBYFQXBObRvhX2UTRTFsUIx7aVp2TCqo4Wpy55EmHJTBzzdzpg8OrE8HQCAq3Z%2B15gl04uaELxklSJR0FTxyEfVdB0et223HSAAvTAAH0CAbJv0dd92K1ZPOC7CPuLgnrYGzHmeLjnrZS9E26qZ%2BryEyE2tk721P0/r7ToKRridQpbk94zrOOOxkB9NH1B8/nxeb7vuixvR/nuQHkAh%2BzqGLg/gTVkxILxXiGqyb%2BrcX7rggXgLuvdoHBhUh6dGqMhoEXRnfNwRcaJkyskBBojhkDdyBnEAgEBv4KEFCQ1MbgL7125BPBs08xQNkrtXNImA642zFMvGOB5paGxPPrV4itCRCBqAIAs2ANYcm1tSayIj5Y0m9t8X4fsBABzBOgCEIcfbqPDl4dEeAsRg2jlTCuVca5cIiAiOk3CG5HkOpAnhsD4GTxcW3TuPcPEEGbj/K%2BI83BjwgEwqeggn4P3QJEx%2BS8bq7hjuvBODot4cxOCnNOkQ7FcIPkuI%2B9k270NcW/FBIBP7AJJOBQQX8/Et2KZgmB7c4E%2BMQQLEpJpUGoDaoQaCDSkHYNSXgmO6pyzENIU0ChtSQBULYDQ8%2BmTbHqhya4twYSWFpjYVYzh6BFn2IYWmPhVMBFFg4IsWgnAACsvA/AcC0KQVAnA3DWGsJ6G4/x7Y8FIAQTQpzFjkhABcjQQp/AXIABygv8GYAAbBoC5XB/AaC4GYC5%2BhOCSF4CwCQGgNCkBuXch5HBeAKBADi75tzTmkDgLAGAiAQDLAIMkLwfcKAQDQAyOgcQIiCk4KoUFUKAC0ULJAXGAMgZAFwpBCjMLwLhhASD5z0PwQQIgxDsCkDIQQigVDqHJaQXQSQADuipkicB4Gcy51yfn3M4LKJljLfSoCoBcXlAqhUirFRKyQUqLgQFaskDlxBITGy4PMXgZKtCLAgEgNl/r6BkBZTGgNIBgBSDMHwOgdJVaUGiFa6IYRGg8lNbwPNzBiA8llNEbQNQyWfLZZ1WUDBaCFt1VgaIXhgClVoFtItpAsDWyMOIFtKtq0mIRFazAqgahMvWJ8iemBzm6toHgaIioy0eCwFa0EeBMXcF4BiOI0ROGJX7cAJdRgfmLCoAYFsAA1PAmADW/huZ8pVwhRDiHVa%2BrVagrX6v0IYYwzzLD6GXcS2A8IQCHrSH3fd8RuB8t%2BfckEmRiUcH5U3JcphLDWDMPi2D9ksBgYgIsDoHEXBOjGH4JIIRpilHKHoGuhQsieFaAxgoHE%2Bh0bmLYedI6uiTEo3oUjdRJicYGBUWwAmWO5GGD0MTswKgkbeWq81HArm4qtQS51fLBXCtFeKyVZgfW4DlYGj5oavkXsWAgTAIVBjEdIP8yQ/ghQAE5/BQkkBoSQZhJAwthVC1zqKODotIJiswrmhSgr8xFjQULAVefi1wKFGndUEqJSSyz5LI00qjXSu1TLyCUETXGrlbAeU6bdYDXMXBItcCFHc2VRACOKtkCqj90gv1KB/bq3QaajU2yLap9TeLeAEttQyplFxHXaddcK6rGlatCnqxoH1fqA1BshRZ8NFK8slbiEV1lXTY2DAW7VrgOKaC0EzcSiAObdUloLT2x7ZaK1VocD2utNYG1Nqta29tnbu27t7fSADg67n4DBrUfdqHGuTuQNOntc6F13KXSugt671h3K3Tuz5sHD1KGPWDicF6%2BDXoUHeh9T6e2vva2qzrshv06ruX1/956sNWGA2jojEAINQfVKQWDpqEPzEWKgZDAhUPob8ZhoDFhcNjfw/nMdkASO8ezuR9w0mqNBCdPJ%2BjSRGMcUE4b9jmR9fceE/xnoJueP2A4t0JoFuJMjNGNroTonaPiYkEplYawffBZG5pzgs3dN%2BRq3Vhrxn8DNc2yGsNVnSA2bs/EBzC7QuYpBQ1qEULQUXL855qErmoVQguSl0b1rCW2EyztnL8A8v0vtYd/bxAyvrFUG6lgCgMTioxEtzk6oZUx/lc3JItP33041fIbrzOdB5AGya3dw3LVpZtQVh1TqO/Cq7z3he/eLRq19cdjb9t/DbdJ3t4/cbm9X8GD36u3c%2B%2Bue7gPgg3ct/puu3EW7927kvebZ8v/m9tWp9l0vWo2s2hDpgG2h2mIEDp8n2mDljrwJDiOjDuOvDojsDsjlamjqujyJjpuvZLjnugekeqDgOiTtlmTkwLeveo%2BnGDTm1hPhIAzpqjPr%2BnkAYOznLiBtEERmLhLgwKhhsAPBzjhnhnEARirg5lbn4BAK4LbjRiUN7qbukMbu7moUxs7kJurg7lJjkDrnIY7lMCoQph7jbpoZJnJl7uYSGksH7ipoHivviiHlvhcDvr3vvnSIfiZrHuZgntltZrZlgKnqphngEBctnrnvniXpIEXiXmXqlq4VXsSqSonk5pFkKokCXv4K5pIHyq5qCkFguv4C4WNpwIERGqptKskRUVXrXosLBukM4JIEAA%3D%3D)

## [Documentation](DOCS.md)

- **Prelude(WIP)**
- **Introduction**
  - [Hello World](./docs/introduction/hello_world.md)
  - [Vocabulary](./docs/introduction/vocabulary.md)
  - [Functional Nature](./docs/introduction/functional_nature.md)
- **Facilities**
  - [Metafunctions](./docs/facilities/metafunctions.md)
  - [Concepts](./docs/facilities/concepts.md)
  - [Utilities](./docs/facilities/utilities.md)

## Performance

Nothing intrinsic prevents Conceptrodon from utilizing a fast algorithm.
While this library requires metafunctions to follow the same pattern, it is uninterested in what is happening within them.
Many functions were tested against **boost::mp11**.
If a function was slower than its counterpart, the implementation from **boost::mp11** was used.
Therefore, This library is generally faster than **boost::mp11**

## Install

Conceptrodon is a header-only library. After downloading the code, move the directory *./conceptrodon* to your project, then use it like your own headers.

You can also install Conceptrodon using CMake:

### Windows

1. Download the library.

2. Open Developer Command Prompt that comes with Visual Studio. Redirect to the library folder. Generate a project buildsystem using CMake:

    ```Shell
    cmake -S . -B "Where to build"
    ```

3. Redirect to the build directory you specified after `-B` earlier. Run command:

    ```Shell
    cmake --install . --prefix "Where to install"
    ```

After installation, add the install directory you specified after `--prefix` to variable `CMAKE_PREFIX_PATH` in your project's *CMakeCache.txt*. If the variable doesn't exist, you will need to add the following line to your *CMakeCache.txt*:

```CMake
CMAKE_PREFIX_PATH:PATH=Install directory of the library
```

If `CMAKE_PREFIX_PATH` already exists,
append the install directory to the values of the variable(note the added semicolon):

```CMake
CMAKE_PREFIX_PATH:PATH=...; Install directory of the library
```

In the *CMakeList.txt* of your project, Add:

```CMake
find_package(Conceptrodon REQUIRED CONFIG)
target_link_libraries(YourProject PRIVATE Conceptrodon::Facilities)
```

You are good to go.

## Links

[Documentation](./DOCS.md)
