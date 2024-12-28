<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Hello World

- [**To Index**](../index.md#introduction-hello-world)
- [*Prologue*](#prologue)
- [*Implementation*](#implementation)
  - [*Failed Attempt*](#implementation-failed-attempt)
  - [*Adopted Method*](#implementation-adopted-method)
- [*Convention*](#convention)

## Prologue <a id="prologue"></a>

Let us examine `boost::mp11::mp_bind_front`.

```C++
template<template<class...> class F, class... T>
struct mp_bind_front
{
    template<class... U>
    // `mp_defer<F, T..., U...>` will instantiate `F` by `T..., U...`.
    using fn = typename mp_defer<F, T..., U...>::type;
};
```

To summarize, `boost::mp11::mp_bind_front` accepts an operation and a list of elements.
Then, it returns a metafunction.
When invoked, the metafunction extends the back end of the previously provided list with its arguments and instantiates the operation with the result.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation
<
    mp_value<0>,
    mp_value<1>,
    mp_value<2>,
    mp_value<3>
>;

template<typename...Args>
using Metafunction = mp_bind_front
<
    Operation,
    mp_value<0>,
    mp_value<1>
>
::fn<Args...>;

using Result = Metafunction
<
    mp_value<2>,
    mp_value<3>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIFmpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmgRHI3lgA1OZmsagZBAD0LKlcXAB0CKmpJyYaAIJv716ZRofMbAUqSYm0OZwuJkCVg%2BPwiwH%2BrEwQJBmEONzukOhnw%2BBEwNwMuMhbgIAE9UoxEfcqZDsF9xsQvA5DgB5cnEJgNTFfL6wv5CLzPDKYdAAJSRXloBGOgQAIiy2RzstzAm4vod1WjUgB9ABuYi8mCJGhppDVGpuuv1hpVXBNZvVFr13mtbjMdo%2BGs1ludRMCNOVtKh3JxeNSBJdpPJAMwVPu72IwAU/phv3hAFlMM0qF4GA5stK5RbYhF0FqqMRZMrVR6NayEoqBKaaw7tU6DUb3e9PY6rUTbYFaR9k%2B8QCAqAwifHE7H/UGhym4YcxQoJVLIXKM1mc3mBFX7V62y63QOm13za3eyq/QOA1z5%2B9Zo5kFqmAolK0ION0KOFIiX0mVWXVdSEOflBSUUVxUlGklkxDgVloTh/F4PwOC0UhUE4VVLGsQ4FDWDZUR2HhSAITR4JWABrAINHuIIAA4zEkeiAE4NAAdgANhY/wuHo6REI4SReBYCQNA0UhUPQzCOF4BQQAksi0Pg0g4FgGBEBANYCFSLwCHISg0BuOgEiiRFOFUejOIAWk4yRDmAZBkEOKR7jMXhhUIEg8G/LgZEEEQxHYKR/PkJQ1HI0hdD8gB3dlUk4HgEKQlDIpk5k9N0qVUCoQ5LJsuyHKclzJDcw4IA8Yz6GIY4zECLgll4JStBWCAkCM1ITLICgIA6rqQGAKQUhoSUEnkiBYki4tmGIElEt4aaWhJZlYm0TAHHm0gjLYQRmQYWg5uU0gsFiLxgDcMRaHk7heCwFhDGAcQjvwYh1scHUkUizBVHWvSthIiJcUE9DaDwWJ2VmjwsEighiDwUSbtID7iDOJQZTxB7QaMciVioAxEwANTwTAYrrVCSP4ALRHEELKbClR1CO6L9AelBrGsfQwfk2BoxAcFxiRkZuCsiiMNSBprusr911MHDLDMaTkbhrBuYgFY7De7IXAYdxPA6PQwgiIZKhGPyiiyAQpj8M2Mgthh5mGRI/I1ndGgmNo9fyZ26k1gQ%2BlaB2Tad2x3atvRZgDo2FlN9WCM2CRko4ZDJLSzg8qs2z7Mc5zXLMcrcC8mriMa0icZWBBMCYLBEjV0hqMkQJ7hYwJ2MkDRJCYzjxP8bj9E4YTSFEyQWPuTj6MCZuuM4swzH8fx2JYlOjpkuSFNL5TWo0tqtMyvSDN61AqtM8yOHyzPDn2B6XJHh50M8ohlb0OnApp6Q6cUBnIt0FI4qYBKbsTsnKSvB0q72yrlM%2BhVL5/C4Dfe4GhyqVU6tVWqyQS7NRUtvPq1V97YJGNAwaLEuASRGriYg41JpHUWrNTa1DlqrTeptbajACB7QOpFE6Z0Lq0CuptO6mMtjoReprD61074/WQH9TagM6iRVBuDJaUNBFNThgjEiyNUaYHRvdIwWNQAbz4PjBQRMSZk02s/amwU36yA/hFJmIAUgGGxrLKwlhOaxFVhAXm/N9LI0SiLJYKxUDi2yJLaWsoXHWAViApWPlPqQHVj7V22tdZ5GtiEHWgdFg22KNkMOOS7ZZNNt0X2bt%2Bj5JKa7f2Awo6O3DqHT26SI41PKHUhqqx1jx3aYJIBqcODpwKvZAh197i33zvgB%2BqCGpNTLqQCuVcRi10EgPUS/haL1S7tPQILdW4d2kMAjCnBV6KVmfXEekhOJcHYrxDQLE6rt3Hn3DggRUrLyOevFqid3JL2ku8jBgTBbkK1pIIAA)

From the template head of `boost::mp11::mp_bind_front`, we can see that one kind of metafunction gets special treatment, namely, the metafunctions acceptable as template arguments for `template<typename...> class`.

Now, let us check out `boost::mp11::mp_fold_q`, a valid operation to pass to `boost::mp11::mp_bind_front`.

```C++
template<class L, class V, class Q>
using mp_fold_q = mp_fold<L, V, Q::template fn>;
```

`boost::mp11::mp_fold_q` accepts a packed container `L`, an initiator `V`, and a quoted metafunction `Q`. Then, it left-folds elements in `L` using `Q::fn` and the initiator `V`.

<pre><code>   L&lt;E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>&gt;, V, Q
-> Q::fn&lt;
   Q::fn&lt;
        &vellip;
   Q::fn&lt;
   Q::fn&lt;
       V, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;, E<sub>2</sub>
      &vellip;
   &gt;, E<sub>n</sub>
   &gt;</code></pre>

With the help of `boost::mp11::mp_bind_front`, we can fix the packed container `L`, and obtain a metafunction that requires only the initiator `V` and the quoted metafunction `Q`; or fix the packed container `L` and the initiator `V` and obtain a metafunction that requires only the quoted metafunction `Q`.

```C++
struct Subtract
{
    template<typename A, typename B>
    using fn = mp_value<A::value - B::value>;
};

using V = mp_value<1>;

using Arg_0 = mp_value<3>;
using Arg_1 = mp_value<4>;
using Arg_2 = mp_value<3>;

using L = mp_list<mp_value<3>, mp_value<4>, mp_value<3>>;

template<typename...Args>
using BindL = mp_bind_front<mp_fold_q, L>
::fn<Args...>;

template<typename...Args>
using BindLV = mp_bind_front<mp_fold_q, L, V>
::fn<Args...>;

static_assert(std::same_as<
    BindL<V, Subtract>,
    mp_fold_q<L, V, Subtract>
>);

static_assert(std::same_as<
    BindLV<Subtract>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/ilpGQLBoREs0bGJtpj2jgJCBEzEBNk%2BftJ2mA6Z9Y0ExeFRMfFJCg1NLbntY30hA2VDiQCUtqhexMjsHOZxIcjeWADU5maRqGkEAPQsyVxcAHQIycnHJhoAgq9vXulGB8xsCmSTA2B1O5xMcSs72%2BIWAf1YmEBwMwB2utwhUI%2B71GxC8DgOQi8kQIxGBBE%2BJgA7JiDrSDgRMNcDAyIW4CABPZKMBEHN6kemc7lsA5WOLYT50g4w35UBhHOIAEVRyQA%2BgA3MReTCst4gEAa7wogC0Ir1Bq1EPFkIplIVGIp0J%2BcIAavKldd1ZrtXE3FxLfb3p9pXC3sRgCqNG7lZ7Day4v7rY7YbywyquFGPebvW5JAnMcGU%2BGzBnVVm43mHV8nQdAiWVbQ8KNWZmveWxfyW7Gfbn29Gyz742KK4H3gymUwWT6OVz/pg7vPQ8AFP6k78LCF0LWIe7VZENyqqMRZM3VfxaOgVQBHfmBFe6kCynVhhTzu7DrFvMfJZnZ6dCucLs%2Bd4FuuDCbq627RnuYEHkeggngengXteNb8s6d56o%2BPqLi%2B87vp8owTngyAqkwChKE0ECjOgeoKAipHLj6Ep0qBm6ss6/KEsSpIOJapDMbSHpnshrKBGhnFEiSZJ3paiwBh%2BhGOCRZEUQQVEEDRIB0WwDGsgJIoboE6E%2BlxUm8e2%2BlCUhV6ieJBKSTx5JDoGYpyZCHDLLQnAAKy8H4HBaKQqCcG41jWAcCirOsKLbDwpAEJoHnLAA1iA3kaHc3lxAAHGYkjZQAnBolIJAV3lcNl0heRwki8CwEgaBopD%2BYFwUcLwCggE1CUBR5pBwLAMCICAqwEMkXgEOQlBoNcdAxGECKcKo2UJEaCSSAcwDIMgBxSHcZi8Jg%2BBEMQeA0VwMiCCIYjsFIl3yEoaiJaQugXQA7qSyScDwnk%2BX5z1tQA8hN40EAcqBUAcy2retm3bbtkj7QcEAeLN9DEEcZhxFwiy8D1WjLBASAzckc1kBQEAk2TIDAFIZh8HQDLEJ1ECRM90GNOy328BzxDsoDkTaJ0PVxTNbCCIDDC0FzvWkFgkReMAbhiLQnXcLwWAsIYwDiLL%2BDEMLeBqoiz2YKonQTZscUhAy1WBQ2kSknzHhYM9JJ4PV6ukMbxCnEoCqMtrDZGIlyxUAYS7OngmBvYDM7c/d13iHd/CCIoKjqLLr36NrKBhZY%2Bh4JEnWwLOIBgqM3tDNwK1JUFyS1AwatGtR26mJY1hmK1PunVgJcQMsHRdM4ECuBMfgXUEsylOUeipOkjfj3PBSN/0M9DBdQ%2BNz04yeK0ehb900xr4MsSb9MS/n70J/zGfg9RRsEi/RwvnNQDnBQyta0bVtO17cWEBcCEBIJjbGuN4qh2WAgTATAsCxAHqQVKkg4h3AKnESkkgNCSDygkRq3lSr6E4LVUg9VJAFTuAkbKcQ0ElQSGYMw3lvKUgKm/WWbUOpdQgb1QmQ0iYjRBhNKalNUBo3motDg0Nv4HD2NrXa5D7iBSOsA3uehU7CFEMnaQaj05PSziAemH0mBfXVs/V%2BLVeBAwEWDCGn8YYbRkb8Lg8i7iRhRiI0m6NQFmHAfjPqfCqboyEQEoYDjaYFS4E1GgtAmYszZrLXmMs4oJIFkLBwCcxaMAIJLaWz15aK2VrQVWCdNZB02IFfWhtjZq0UebZAlsE422qM9B2Tt2QuzKXjU6ns4o%2Bz9pgAOWsjDB1ANwvgEcFBRxjnHRgCc1FJ1ulo2QOjM6BV0PTAwId25WALg7fuEAy4V0mj7b6tdFjLFQA3TIzdW6Ki2Z3buMRe4m0gIPaohsR5jz3rkSeYEb6zwuvPQoWQvkT3yAvTIfyN5VBqEfXol9oXvIYDvGYJRT4HwviC9F19p5opxisNYj88XVTMe/DgtipGhLkXcBRyMgEnVATjPGkDSDQNgUMBB1ViH1XSncbGuC6FxHQRg7B0hzFBU4Bw7qzKkHkMkAkLglJyoaAKljLBVDCEcDiP9NhEquEE2fgdVhrVdW%2BLOVXZmmR/BAA%3D)

But is this what we want?
Isn't fixing the first several elements inside `L` more interesting than fixing the whole thing?
`boost::mp11` has a function to do just that. Introducing `boost::mp11::mp_bind`, a quoted metafunction that implements the type-based equivalent of `std::bind`.

```C++
template<typename...Args>
using Bind = mp_bind
<
    mp_fold_q,
    mp_bind<mp_list, Arg_0, Arg_1, _3>,
    _1,
    _2
>
::fn<Args...>;

static_assert(std::same_as<
    Bind<V, Subtract, Arg_2>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM6SuADJ4DJgAcj4ARpjEIADspAAOqAqETgwe3r7%2ByanpAiFhkSwxcYl2mA4ZQgRMxARZPn4BldUCtfUERRHRsQm2dQ1NOa1D3aG9pf3xAJS2qF7EyOwc5gDMocjeWADU5mZRqKkEAPQsSVxcAHQISUkHJhoAgk/PXmlGu8xsCklMK12RxOJnWVheH1CwG%2BrEwfwBmF2FyuoPBrxeCgIxC8Dl2Qi8USxAIIbxM8TRu0puwImAuBhpoLcBAAnklGLDds9SNTWey2LsrOtsG8qbtIV8qAx9usACJIpIAfQAbmIvJhGc8QCAVd5EQBaAVanVq0HCsGk%2BIy1GkiGfaEANWlcouytV6vWbi4putLze4uhz2IwAVGid8tdusZ6295ttUM5QYVXDDLuN7rckhjaP9CeDZhTirTUazNvedt2QQLCtoeExjNTbuLQu5DcjHszzfDRY90aFJd9LxpdKYDI9LLZP0w12ngeACm9ca%2BFlC6CrURXpI9IqpLv4tHQCoAjqRt5SXeuGOh64qa5jubOQ/fE1xuQre9gTy9RUnP89v2ZN2FF4tUlDUgwUadrn7dFnkxEc8GQBUmAUJQGggTF0C1BRYSQ%2Bcty/Kll0vRl7W5fFCWIYknzzU1f1FXdPAPQ9GSCblSLxAkiQcBdXiFWZUQ4eZaE4ABWXg/A4LRSFQTg3GsaxdgURZlkRDYeFIAhNEE%2BYAGsQBEjRrhE9YAA4zEkEyAE4NHiAA2SyRK4EzpGEjhJF4FgJA0DRSAkqSZI4XgFBAHzNMkwTSDgWAYEQEBFgIJIvAIchKDQC46FicJYU4VQTNsvVbMkXZgGQZBdika4zF4TB8CIYg8Ewl9%2BEEEQxHYKQZEERQVHUcLSF0F8AHdKKSTgeCE0TxK06TOAAeSSxKCF2VAqF2XL8sK4rSvKyRKt2CAPHS%2BhiH2Mx1i4WZeDCrR5ggJA0qSDKyAoCAHqekBgCkAIaFoGliGCiAommi96mZMbeBB4hmVmqJtCqML1LSthBFmhhaDBvqsCiLxgDcMRaGC7heCwFhDGAcRMbwYh4bwJU4WmzBVCqJLVnU0IaVcqSayiSioY8LBpqxPBPKJ0g6eII4lBlWkyZrIwtPmKgDDne08EwQbZoncHOuEURxA65r5CUNRpoG/QyZQeTLH0PAomC2BJxAYE73Fsa8u06SkkcARCb1DDQRlUxLGsMx/PF%2BqsHtiB5jab2/AgVwRj8F9gkmEoyj0FI0jjpPM/yOOenT/oX1jmpxlzkvMHsOPOgaQu%2BjiEvy88Zo9Dguu04biQY%2BUlZu/0SbfOmgK1rygqipKsqKvzCBcEIEhTvOy6NIV%2BYEEwJgsDiaPSD0yR1muSz1niSQNEkczbO8kT7IHtyPJASRLKMswROswqj9M9ZbMSPzeACoKQor3CrdGKd04oLSSilV6qAjqZWyhweoLAlTxD1EwXY2wyblSfjcKSNV54Rz0IbVq%2BtpCG26ibPqugAjDSYKNImE0OBiSHn1AK80EpJWWqtda490EGC%2BFwbB1xQwHRgY9Y6i8zDL2uhFMBb1jpQLkf0DBRgBFcB8j9P6AMgZ9UhhjdSuiYZwwcNrJGjACCo3RtNLGOM8a0AJtrEmstVhSXwNTaodNCa4KZsgFm2t2ZV2mtzXmzJ%2BbOKuvVEW6lxaS0wNLUmRg5agGAXwZWChVbq01owbWRC9btVIbIchvUpJUPNvLIOVhrbcyjhAR2ztkqu24O7WY8xUBewyL7f2spykhzDrECO9NIAxyrjTZwCdLwV0CJeeu0xG55GzhkCZWcCgMGmRnSu1cy5dAmaXDo4xVnF0GFsluOQm5dH2Y3HuSw%2B4XVvkw3%2BM0OCjw2kVZR0IBHXBwftOedVF4XSuqvUg69N79B3q5dypBPIGWuJIE%2BGgj4GVsrZLgtl1jX2Yf5TgADQoAr3k/SQSL4iOThWdM%2BJl1i33WFNFhmKgE3QYVVdFf8aXSOaWLWIaRnCSCAA%3D)

`boost::mp11::mp_bind` works creatively.
Not only does it replace the placeholders in its argument list, but it also detects the 'binding' structures in its arguments and replaces their placeholders accordingly.
The result, however, is slightly arcane.
Moreover, since each placeholder indicates a single item in a list, the function cannot express the rest of the arguments using a pack expansion.
Therefore, we must decide beforehand the total number of the required arguments for the target operation, even if the operation is variadic.

Alternatively, we can use `boost::mp11::mp_compose` to inject the result of `boost::mp11::mp_bind_front` to the first parameter of `boost::mp11::mp_fold_q` with the help of `boost::mp::mp_bind_back`.

```C++
template<typename...Args>
using BindAlt = mp_compose
<
    mp_bind_front<mp_list, Arg_0, Arg_1>::fn,
    mp_bind_back<mp_fold_q, V, Subtract>::fn
>
::fn<Args...>;

static_assert(std::same_as<
    BindAlt<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);

using Arg_3 = mp_value<2>;

using L_1 = mp_list<Arg_0, Arg_1, Arg_2, Arg_3>;

static_assert(std::same_as<
    BindAlt<Arg_2, Arg_3>,
    mp_fold_q<L_1, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwc5gDMYcjeWADU5mbRqGkEAPQsyVxcAHQIyclnJhoAgh%2BfXulGx2YbAUySYW2OFyuJl2Vi%2BfzCwEBrEwILBmGOdwe0Nh3y%2BM2IXgcxyEXmiBGIYIIPxMAHYcccGccCJg7gZmdC3AQAJ7JRjI46fUhMnl8tjHKy7bA/RnHeEAqgMU67AAiGOSAH0AG5iLyYDmfEAgbXedEAWnFhuNuuhUph1Jpyux1Lh/0RADUlaq7lqdXrdm4uDanV8fnLEZ9iMB1RpPWqfSaObsg3aXQiBZH1VxY96rX63JJkziw%2Bmo2Zsxrc4nC87fq7jsFy%2BraHgZvqM4ES5mhRHS9WQ19maymOz/dzeUDMI8pz2FEHUwCLGF0J9aARG2g7mk9SH/dLGd7okv1VRiLIOd7mzNu%2B3r1HA5LDQrSHuGQej9EwQBrc8a/i0dDqgAjkKbpCiSZIUg4NqPgw1KSj8MFtsAChTo8fa4p8MzDngyDqkwChKM0EAzOghoKMieGzruXwyouDDLquSHqmYNrPjR%2B6/p4AGARywQgWBpLkpSc7fJKyzBhhxY9uquyNpW/osfBKaSXWwSZo2l5Uv60kdtJXC3sxBlJkpOI/Fhji4fhhEEMRBCkSA5FsJRHIvuKS4rlpbjSWYRmsa53p/txvFdscoHEoJkFaVKO7YOJMIcKstCcAArLwfgcFopCoJwbjWNYxwKOsmzonsPCkAQmgJasn4gMlGiPMluwJGYkgJAAnBoNIAGxtclVTSElHCSLwLASBogTpZl2UcLwCggIEFUZQlpBwLAMCICA6wEMkXgEOQlAbskdBxBEyKcKoCRdaaXWSMcwDIMgxxSI8Zi8Jg%2BBEMQeCkfp/CCCIYjsFIMiCIoKjqEtpC6PpADuFLJJwPCJSlaWVVlnAAPK7Tta6oFQxwXVdN13Q9T2SC9xwQB4dzHcQpxmLsXDLLwi1aKsEBIIdtP7RAXP0PEwBSD5NCrnEc0QNEaOHswxBcojvDS00XIY9E2i1ItZUbmwggYwwtBy5DWDRF4wBuGItBzdwvBYCwhjAOIht4MQ6t4JqKJo5gqi1Lt2xlWEzKDZlzbRBSsseFgaPkngo1W6QbvEBcSjKiydvNkYlWrFQBjIW6eCYDDGPjvLIPCKI4jA398hKGoaPQ/odsoHllj6Hg0RzbAE4gJCV7x4jl1VVlyQ9JbpokdCyqmJY1hmFN8dfVg7cQKsNR1M4ECuJMfj6SE8xlBUegFBkAibwfaRHwwgx70snTdPUswn/pK89H0zSX8MlRjP0D%2Bf6/u/vxIy8ipbAAfoFGpBJq8GmgTS611br3Ues9MsEBcCEBIPTRmzNyoZ1WAgTATAsDxCXqQGqkhdiPDarsGkARJAtS6uNZKPVQFDRGv4NqjwuoJF2BQ7qXUzBmGSslGkbVwFo2mrNeaWClrs3WhzTa2Ndo8z5idM6HBCawOOIcO2T02FPEyu9VB889CVwBuXaQlcwY10hroHycMmAIytsjDgqURGQ2mljbau1jh42gUTW6miARcB0Y8GMVNUA035ugswmDWbLVkUosgFBeZhKOvzFABgjCBK4IEEWzJiDi0lpDRWsti5FOVqrdWxctaMAILrfWaMjYmzNrQC2xcbap22JlfAzs6hu0tnor2yAfbF39l0NGwdQ5cnDh0lmX0Y5lXjonTAydbZGDTqAKRfBs4KFzvnQujBi7GLLkDMxsgLEQ0ytY%2Bu6dJ5WGbsHReEBO7dz2r3bg/dlirFQEPTII8x4qhudPWecR57u0gMvLoLs14b08G0PQO9Sj/30ofHo39kWZDfosD%2BT875fxhbkR%2BELV69FmBi/ej9754q3j/OYCLMUgMKhsYBTMmHOIgejDgPj1H%2BMRIEx4ujKYoM%2BugpmLNsGkFwfgkYRCapZMCINYapBRp1UeIzOhvDdiUKoTQ6QbKxG2D0DEj5xDWGPEkF1LgNI%2BoaDagzDQrVdhMN2KjVxnBRVSMca9FxU1XWSLZqseO6RnCSCAA%3D%3D%3D)

This method allows appending a variable number of elements to the end of the target list.
However, the technique is convoluted and not so adaptable to general cases.

Overall, I'd like the composition to be more intuitive and the technique shall be consistent throughout the library.
The reason why we find it difficult to handle the target list in `boost::mp11::mp_fold_q` is that the list is sealed inside the container `L`.
`boost::mp11` introduced the idea of 'quoted metafunctions'
Why don't we expose the target list using a member template, turning `boost::mp11::mp_fold_q` into a quoted metafunction?

```C++
template<typename V, typename Q>
struct QuotedFoldQ
{
    template<typename...Args>
    using fn = mp_fold_q<mp_list<Args...>, V, Q>;
};

template<typename...Args>
using BindOpt = mp_bind_front
<
    QuotedFoldQ<V, Subtract>::fn,
    Arg_0, Arg_1
>
::fn<Args...>;

static_assert(std::same_as<
    BindOpt<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQgAMwAHKQADqgKhE4MHt6%2B/ilpGQLBoREs0bGJtpj2jgJCBEzEBNk%2BftJ2mA6Z9Y0ExeFRMfFJCg1NLbntY30hA2VDiQCUtqhexMjsHOZxIcjeWADU5maRqGkEAPQsyVxcAHQIycnHJhoAgq9vXulGB8xsCmSTA2B1O5xMcSs72%2BIWAf1YmEBwMwB2utwhUI%2B71GxC8DgOQi8kQIxGBBE%2BJgA7JiDrSDgRMNcDAyIW4CABPZKMBEHN6kemc7lsA5WOLYT50g4w35UBhHOIAEVRyQA%2BgA3MReTCst4gEAa7wogC0Ir1Bq1EPFkIplIVGIp0J%2BcIAavKldd1ZrtXE3FxLfb3p9pXC3sRgCqNG7lZ7Day4v7rY7YbywyquFGPebvW5JAnMcGU%2BGzBnVVm43mHV8nQdAiWVbQ8KMdamNPzQ%2BGuG3U2YK4H3gymUwWT6OVz/ijnfzR0KUQBFf3Ykl4ggHWdeVAM9AAMU86HngepErpA%2BSzOz0/Hdyv7YUC7ekoLsrr/Fo6BVAEdWR6G02fTer3clr8pOq69h8toBlibwnmerIXgiAE3neBYWCE6AAPLJCuELuqqkRoSqVDELIFI%2BketJrhumDbru84%2BiBhLEqSDiWnqsqkORhYRl2HakeK7xsQwzbAAoAFgZ8oxDngyAqkwChKE0ECjOgeoKAism3mR7ySqhDAYVhwkqj2YocdpdIei%2Bb6fj6gTAfyjEkmSd6WosGIcMstCcAArLwfgcFopCoJwbjWNYBwKKs6wotsPCkAQmjucsADWIBeRodxeYkZiSAkACcGiUgAbLlXlcAk0ieRwki8CwEgaK2fkBUFHC8AoICtvF/nuaQcCwDAiAgKsBDJF4BDkJQaDXHQMRhAinCqAkhVGoVkgHMAyDIAcUh3GYvDUYQJB4Cpnb8IIIhiOwUgyIIigqOoXWkLonYAO6ksknA8B53m%2BQlgWcOho0jSuqBUAcC1LSta0bVtkg7QcEAeFN9DEEcZhxFwiy8J1WjLBASCTck01kBQEAE0TIDAFIZh8HQDLEG1ECRL9%2BHMMQ7IfbwLONOy6GRNonSdbFk1sII6EMLQ7MPVgkReMAbhiLQbXcLwWAsIYwDiFLeDEALeBqoiv2YKonSjZssUhAylUBQ2kSkmzHhYL9JJ4LVyukPrxCnEoCqMurDZGAlyxUAYInOngmDPZhjAc9dwiiOIV2nfIShqL9T36OrKChZY%2Bh4JEbWwOOIBgqM7tDNwi2JYFWGZErRrKThpiWNYZhNR7xBHQbkDLB0XTOBArgTH4nZBLMpTlHoqTpLUWSeK0k8FDP/Tj0Mna9zPPTjHPuRr9Uut1NMy%2BDLEa/TEPeiSU0R/zCfPeRRsEhfRwPmkI1vDNWDi3Lat62bdtxYQFwAdFGMVMZxUDssBAmAmBYFiBAZK/g4h3FynESkkgNCSGyoVeqXlir6E4NVUgtVJC5TuIVBIcQUFFUKmYMwXkvKUlyq/X6zVWrtXAV1XG/U8aDUBqNcapNUBIxmnNDg4Nv4HD2OrLapD7gBX2kQDux1Y7nQTtIJOt1U4PV0NTV6TB3rKyfi/N%2Bf0OAA2GqNA4INP4Q1WlI34XBZF3EjAjIRhNkaoziGYMB2Nuo8LJsjARAShj2MprlLgrYaC0DpgzJmD0uZsxjgknmfMBYx2FowAgYsJa/WlrLeWtBFYx1Vn7TYAV8A6y6PrJW8jjbIFNjHC21Rfo2ztuyB2ZSsYd1drFD2XtMA%2BzVkYf2oBOF8BDgoMOEco5%2BViknVRl11GyE0fdAKOiM4ByblYHONsC5QCLiXMaHsPqV0WMsVANcBB1wboqLZLc24xCUV3eBVQaiZBcHpc%2BI89LXwnp2KehRZ45GHvkaemRfmr1efvBgm9mjbxBevboh8x7HwvmfeFaLegQtvisNYD8Mb4Ofj9B6H9xGQ1CTIu4cj4ZAMUZ4jGWMIGkCgTAoYLzKqENqmlO46NsE0LiKgtBmDpAmNYbYdhvizmkBSiQu4khCpcEpKVDQuU0YYIoYSuIxKmqcEZZwp%2Bu1mEkt1RwnGywPbpGcJIIAA%3D%3D%3D)

Conceptrodon was created based on this idea.
By exposing different kinds of parameters using member templates, this library unleashes the potential of pack expansions and allows us to handle each kind of parameter independently.
The previous example will look like the following if metafunctions from this library are used.

```C++
template<typename...Args>
using BindAnother = Mouldivore::BindFront
<
    Mouldivore::FoldLeft<Subtract::fn>
    ::Mold<V>
    ::Mold
>
::Mold<Args...>;

static_assert(std::same_as<
    BindAnother<Arg_0, Arg_1>::Mold<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAHKSuADJ4DJgAcj4ARpjEEhqkAA6oCoRODB7evgHBaRmOAuGRMSzxiVzJdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHMxsCilM2wDUALIbtPgAbiSYxyYA7FYaAIImrwD0AFQ/X8cAYp50KFMFQCMdfl8Pu8XgRMCwUgY4SZ/G44QikZgUWiAJ4pRisTAAOhJKOwx2QBgUCmOAHl8cQmL0yTDZsQvA4AUCQWCYY9ni9jkLjujEUysaiCHiCWxjgBJBiZJkkFmvYXHNkc8HKYioIjnS4w9X8o3q4WizHYqX4vbEknYehsQQKVWCs1CzWcgAimCadHuT0eXpRAtN7o%2BH2OFiYSmObhj7D5avdxwjXMuxwE2yJYbNFvFVultuODvhjAIrpTGoI7O9vqYdGxpadFf82FzxsDyarQq8GSMIul938XrpDKZWWxCqVRDIJcd5ZZ/gFVaDIaTbvDkcBGYIAHc8NmO%2Bb4WLkZKi4SAXhiLNSIObVehHUBOhKynPeCfX7aNj/je72OZ80AYN822PIUTW7Hs%2BwiYAHyxaDVxHYV6QSCcBGxCCezQxlmVRbCe2FadHGVOd/1vCskKI4dsHvYDX0IlMlxXZiHmDZcNyrNMACU6k2DIrjueMlBALiUzTHd0BFA9tnvBBDHQegRQQO4aEomTUGOQ5GTYOFb1IbC00U45iH4287lggcCFU0zMFmHNqKFfNz1xR9ZQowDrRlO4GNA%2B9vNtEkiVpGyEhdcCnOrWsv3rRtUU8gh6Jffy6TC29gvfd0oM3GD%2B3g7ymMglCdT1VADTfKLjQIqqU1wjCGCw2r3Xq/C3CKnsSLwMj70SjrqrooCUsq3KaNojqyRAEAXLub8G1/VFQtUjLSTbKbCs4qK102t4opmwt3LtIkXmAMyy2dLKzSs%2BCKuHUc5vitwTrOlsFEytbpulddoO20NoP2i9DuC57MHOggIvbaDrrOIE7uOUr9SBbEQbBt7VvbHbfo3b5fijCJ0H%2BXVBAhX5oVeAG0VPS1AZ897yUpGMaVaydIpeT88dAwnZD5LtcopwLCWCixMGACJFSMCHc3ZhHyqRn7earfnLzYYLm3LSWouh26UVHZnMNRYXRYYcXgDRol7zV506e%2B3KsdeXMlaBklDbFuCNdyrXYZ1%2BHdURw0DZF12JetzH2Jtnng3t%2B2zH8CJKS8LB7jMMxYlQdICA%2BBEuC4IkEBSFJzDMDdodtA4jjuVP05tkvCTLk4s64cPXnZoQvFiGsjiot4FZPDECxp4sXgC5W7isVn1WhqgGDhhEAH0rjELwJSeqaF%2B8O4AFoo1XxeJQx0Mw8x15oYANRnlJ5937FG/Ao%2BXmhl5iGAWeNHPy/1%2BxfwWJhB%2Bn9nrg35ryXtiSQ39j75WOI/Z%2BZhAFX1RF/W%2Bf174QNCG/WgeBZjIz/skSBf8uD3igbPIuiCNyO1piSKB7toYWHxi8Bgeplpw3OF4S4eAbhmSmjQzmRMu5NVysw1h7D2AgCkjyVsbhW7t0ZA4KaU9LpTQqtiE%2B8iQCKPtqzBRSNUSUJDkg2YE5kCz0ZgkAgEBZjoCmgoQkRiIrtWglw9AdCGEJCwc/HBhCb7YE0f7J6f9iF0VzHPfglxZ4AEdsShHvCfeibcO4OFdGSFYIYOBrFoJwAArLwPwHAtCkFQJwdqlhrAag2FsO45h/A8FIAQTQKS1gAGsQDpI0ESdJQQzCSECAATg0A8AAbF09JXBAjSDSRwSQvAWBJGSNk3J%2BSOC8AUCAZINSckpNIHAWAMBEAgA2AQFIXgkoUAgGgBEdAEhREJJwVQgQ%2Bkbz6ZIY4wBkDIGOFIIkZheCYHwLOPAFj8H8EECIMQ7ApAyEEIoFQ6g1mkF0PgvcjIUicB4KkjJWTal5M4LSQ5BzwSoCoMcG5dyHlPJeW8yQHzjgQA8Gc%2BgxAk6VJWLwVZWg1gQCQKclI5yyDHM5dykAwApBmD4HQfSSyICxAxbECIzQcTIt4NK5gxAcS0liNoOoqyqmnJbLSBgtA5UwqwLELwwB4y0FoEs7gvAsAsEMMAcQhqbwarYfZDFmBVD8ThPK8gghugYvQbERkyqPBYAxTWPAUyrWkCEsQVOSgfS2qMOgowtS1hUAMKbE%2BeBMB7jQtkqpgLhCiHEGCwtkK1AYrhfoO1KBrDWH0HgWISzYC2hAJXO8MbkW3LqXklIvRLUb3MTrUwRTLBmDmTG4gfzXWQDWLUeozgICuCmH4fBYQFjlEqHoQomQBAru3ekXdDAhibuWF0HoDQ5j7vwfO3o/QWgnpGFUcYAxr0vofRup9Eg52lO2N%2B/QaLSCzN4PMwltz7mPOea895MCIC4EICQBlXAmXVNTWsVSTAsCJAgA0kAkh/BEi6f4B4kgNCSA6X0jQGh0kDIA%2BMyZeGulEj6YEfwRH%2Bl9OTuk9JDwulAYxfMxZyzUNrLZds9luycWHPIJQPldLLlsGueBklDMBxcCYznXJ3yENTv%2BeCotIKJDSDLUoCtMLdDCoRUwJFVrUUcEyfxmF8zsX7MOZmAlRKIMUgMGpjTRJX7UtQLShIDKzAoZZesiTcmEgyZOUFrldKUA%2BcFV06oIraBisoJKmFirZXety8q1V6qZFRu1eWXV%2BqMVGpNWai13qbV2odbk/AZl6hCUtVpj1yBDk7CqREOEYzckBqDTiENOxcnhsjVUmNcbMAJsa3BVNfAM0KCzTmvN3rC3ApLcZ2Q5boW5Is9WlNI6rCWAbU2%2BAEBW3tqSp27g3aVhrFQH2rIA6h0jlO9YcdIHJ3TubTh89zrF3Ls8O0PQ66yhfvwTu3ob7YdZEfUsZ9t7L2vrB3kG93Rgd9DmEjrdN6r0Y9Xe%2B%2BYUPkf/oUL%2B0FdmHPAcxRwMDxLHmqfgupokmmqXwdnEh8LaHSAYaw5QOzEzSBTOaUSSplHOP%2BGIyR8j0h6eCdsMJiLT3SCNMkExyQfSuAPCGRoLpMcyOsbo/4dFTnODMv52Mz5jm5lW5E6ytYMaMjOEkEAA%3D%3D)

## Implementation <a id="implementation"></a>

In the terminology of `boost::mp11`, the phrase 'quoted metafunction' refers to a class containing a metafunction member `fn`.
In a sense, the surrounding class acts as quotation marks.
However, I would like to think of it differently.
The word 'quoted' also describes a passage taken from a context.
In the documentation of `boost::mp11`, after instantiation, a metafunction is often said to return a quoted metafunction, meaning the instantiated surrounding template is considered a part of the result.

> `mp_not_fn<P>` returns a quoted metafunction `Q` such that `Q::fn<T…​>` returns `mp_not<P<T…​>>`.

```C++
template<template<class...> class P> struct mp_not_fn
{
    template<class... T> using fn = mp_not<P<T...>>;
};
```

In my opinion, invoking a metafunction creates contexts for its member templates.
Using such members is similar to quoting texts from an article--we quote members from an instantiated metafunction.
Therefore, for the purpose of this library, the term 'quoted metafunction' is better used to describe the member templates, and  'returning a quoted metafunction' returns a member template without quotation marks.
Following this thought, we will implement our metafunctions in such a way that the contexts are built up in steps, allowing manipulations to happen within each step before finally returning a quotable result.

### Failed Attempt <a id="implementation-failed-attempt"></a>

One way to do so is to accept different kinds of parameters using nested class member templates.
We will soon see the limitations of this method.

Consider the following example:

```C++
template<typename...>
struct Example
{
    template<typename...>
    struct Mold {};
};
```

This is quite straightforward.
However, such simplicity comes at a cost.
Namely, defining a member with the same name as its surrounding class is forbidden in C++.
Therefore, the following code won't compile.

```C++
template<typename...>
struct Example
{
    template<auto...>
    struct Page
    {
        // Error: Member 'Page' has the same name as its class
        // clang(member_name_of_class)
        template<auto...>
        struct Page {}  
    };
};
```

Assuming we are creating a metafunction that transforms the variable at a given position in a sequence, invoking the metafunction by

```C++
Metafunction<Transformation>::Page<Index>::Page<Variables...>
```

is impossible since class member templates with the same name cannot appear adjacent to each other.
Note that `::` indicates a nesting relationship on this occasion.

One solution is to add a separation structure between the class and its problematic member.

```C++
template<typename...>
struct Example
{
    template<auto...>
    struct Page
    {
        struct Slash
        {
            template<auto...>
            struct Page {}; 
        };
    };
};
```

Recall the metafunction we wanted to create earlier.
Invoking the metafunction by

```C++
Metafunction<Transformation>::Page<Index>::Slash::Page<Variables...>
```

is now available.

However, this creates another problem.
Assume we inherit `Page` to a new name, say `Road`.

```C++
template<typename...>
struct Example
{
    template<auto...>
    struct Page
    {
        struct Slash
        {
            template<auto...>
            struct Page
            {
                static constexpr bool value {true};
            }; 
        };
    };

    template<template<typename...> class...>
    struct Road: public Page<> {};
};
```

Since the name of the surrounding class changed to `Road`, the separation structure surrounding the nested `Page` is unnecessary, yet we still have to go through `Slash` to access this inherited `Page`.

```C++
static_assert(Example<>::Road<>::Slash::Page<>::value);
```

In addition to this, assume the inherited `Page` contains a member also called `Road`.

```C++
template<typename...>
struct Example
{
    template<auto...>
    struct Page
    {
        template<template<typename...> class...>
        struct Road
        {
            static constexpr bool value {true};
        };
    };

    template<template<typename...> class...>
    struct Road: public Page<> {};
};
```

A separation structure is needed since `Page<***>::Road` has the same name as the new surrounding class.
Otherwise, the constructor of the descended `Road` will hide the name of the inherited one.
We can no longer access the inherited `Road` from `Example<***>::Road<***>`, as `Example<***>::Road<***>::Road` will always refer to the constructor of `Example<***>::Road<***>`.

```C++
// Error
static_assert(Example<>::Rail<>::Rail<>::value);
```

These behaviors are not predictable by higher-order metafunctions.
Probing into arguments' inner structures to cross potential separation structures is necessary before every operation, which is complicated and inefficient.

I first wrote the library using this method.
Convoluted machinery was employed to remove or add separation structures whenever necessary.
As a result, I implemented a seemingly simple metafunction `Skip` using pages-long macros and still could not handle all the cases.
The added complexity was daunting and opposed to the goal of making metafunction composition intuitive.
I gave it up.

### Adopted Method <a id="implementation-adopted-method"></a>

After studying `boost::mp11` and `kvasir::mpl`, I adopted another approach, which uses alias member templates for interface and class member templates for implementation.

Consider the following example:

```C++
template<typename...>
struct Example
{
    template<typename...>
    struct ProtoMold 
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold 
            {
                struct Slash
                {
                    template<typename...>
                    struct ProtoMold 
                    {
                        static constexpr bool value {true};
                    };
                };
            };
        };
    };
};
```

We still face the problem as before.
Separation structures are necessary between adjacent class member templates with the same name.
However, since the name of an alias template won't be injected into the instantiated class that it eventually refers to, we can reuse the name inside the said class.

```C++
template<typename...>
struct Example
{
    template<typename...>
    struct ProtoMold 
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold 
            {
                struct Slash
                {
                    template<typename...>
                    struct ProtoMold 
                    {
                        static constexpr bool value {true};
                    };
                };
    
                template<typename...Agreements>
                using Mold = Slash::template ProtoMold<Agreements...>;
            };
        };
    
        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

This means the navigation within a class can be hidden inside the aliases, which consist of the interface of our metafunction.
The arguments will be redirected to class templates for further processing.
Since the class templates are not exposed to the users, we are not forced to name them following a rule.
For example, we can avoid adding separation structures by using the names `ProtoMold_0`, `ProtoMold_1`, and  `ProtoMold_2`.
However, we will follow the convention at the end of this article.
This is because some metafunctions are implemented using macros.
The fewer unique names there are, the fewer macros I need to write and the fewer mistakes I would make.

However, this method brings a new problem.
Since the interface of our metafunctions primarily consists of alias templates, a peculiar behavior of alias templates must be noted.

Consider the following example:

```C++
template<typename...>
struct Example
{
    template<auto>
    struct ProtoPage {};

    template<auto I>
    using Page = ProtoPage<I>;

    template<auto...Variables>
    struct Detail
    {
        // Error
        using type = Page<Variables...>;
    };
};
```

It fails since pack expansion cannot be used for a non-pack parameter when instantiating an alias template.
To circumvent this limitation, we require the parameter list of every interface alias to contain one parameter pack and nothing else.
This restriction is also shown in our definition of `conformed metafunctions`.
Such metafunctions are the primary focus of this library.
We will discuss them in Vocabulary.

Following this restriction, we must introduce a layer of indirection when implementing `Capsule`.

```C++
template<typename...Elements>
struct Capsule
{
    template<template<typename...> class Container>
    struct Detail { using type = Container<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    // Instead of: 
    // template<template<typename...> class Container>
    // using Road = Container<Elements...>;
};
```

This is the method used throughout the library.

## Convention <a id="convention"></a>

The following example shows the complete layout of a general function.

```C++
// Define dummy placeholders for readability.
#define TEMPLATE_PARAMETER_CATEGORY auto
#define TYPE int
#define VALUE true
#define CONTENTS
#define IMPLEMENTATION int
#define POSSIBLY_A_TEMPLATE

template<TEMPLATE_PARAMETER_CATEGORY...>
struct Example
{

/**** Type Result ****/
    using type = TYPE;

/**** Value Result ****/
    static constexpr auto value {VALUE};


/**** Mold ****/
    template<typename...Elements>
    struct ProtoMold
    {
        struct Slash
        {
            template<typename...Arguments>
            struct ProtoMold{};
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    using Mold_t = Mold<Args...>::type;

    template<typename...Args>
    static constexpr auto Mold_v {Mold<Args...>::value};


/**** Page ****/
    template<auto...Variables>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    using Page_t = Page<Args...>::type;

    template<auto...Args>
    static constexpr auto Page_v {Page<Args...>::value};


/**** Road ****/
    template<template<typename...> class...Containers>
    struct ProtoRoad {};

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class...Args>
    using Road_t = Road<Args...>::type;

    template<template<typename...> class...Args>
    static constexpr auto Road_v {Road<Args...>::value};
    

/**** Rail ****/
    template<template<auto...> class...Sequences>
    struct ProtoRail {};

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<auto...> class...Args>
    using Rail_t = Rail<Args...>::type;

    template<template<auto...> class...Args>
    static constexpr auto Rail_v {Rail<Args...>::value};
    

/**** Flow ****/
    template<template<template<typename...> class...> class...Warehouses>
    struct ProtoFlow {};

    template<template<template<typename...> class...> class...Agreements>
    using Flow = ProtoFlow<Agreements...>;

    template<template<template<typename...> class...> class...Args>
    using Flow_t = Flow<Args...>::type;

    template<template<template<typename...> class...> class...Args>
    static constexpr auto Flow_v {Flow<Args...>::value};


/**** Rail ****/
    template<template<template<auto...> class...> class...Stockrooms>
    struct ProtoSail {};
    
    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;

    template<template<template<auto...> class...> class...Args>
    using Sail_t = Sail<Args...>::type;

    template<template<template<auto...> class...> class...Args>
    static constexpr auto Sail_v {Sail<Args...>::value};


/**** Snow ****/
    template<template<template<template<typename...> class...> class...> class...Sorrow>
    struct ProtoSnow {};

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = ProtoSnow<Agreements...>;

    template<template<template<template<typename...> class...> class...> class...Args>
    using Snow_t = Snow<Args...>::type;

    template<template<template<template<typename...> class...> class...> class...Args>
    static constexpr auto Snow_v {Snow<Args...>::value};


/**** Hail ****/
    template<template<template<template<auto...> class...> class...> class...Melancholy>
    struct ProtoHail {};
    
    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = ProtoHail<Agreements...>;

    template<template<template<template<auto...> class...> class...> class...Args>
    using Hail_t = Hail<Args...>::type;

    template<template<template<template<auto...> class...> class...> class...Args>
    static constexpr auto Hail_v {Hail<Args...>::value};


/**** Cool ****/
    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    struct ProtoCool {};

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;

    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    using Cool_t = Cool<Args...>::type;

    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    static constexpr auto Cool_v {Cool<Args...>::value};


/**** Calm ****/
    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    struct ProtoCalm {};

    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = ProtoCalm<Agreements...>;

    template<template<template<template<template<auto...> class...> class...> class...> class...Args>
    using Calm_t = Calm<Args...>::type;

    template<template<template<template<template<auto...> class...> class...> class...> class...Args>
    static constexpr auto Calm_v {Calm<Args...>::value};


/**** Grit ****/
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    struct ProtoGrit {};

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = ProtoGrit<Agreements...>;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Args>
    using Grit_t = Grit<Args...>::type;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Args>
    static constexpr auto Grit_v {Grit<Args...>::value};


/**** Will ****/
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    struct ProtoWill {};

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Args>
    using Will_t = Will<Args...>::type;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Args>
    static constexpr auto Will_v {Will<Args...>::value};


/**** Glow ****/
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoGlow {};

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = ProtoGlow<Agreements...>;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    using Glow_t = Glow<Args...>::type;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    static constexpr auto Glow_v {Glow<Args...>::value};


/**** Dawn ****/
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoDawn {};

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = ProtoDawn<Agreements...>;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Args>
    using Dawn_t = Dawn<Args...>::type;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Args>
    static constexpr auto Dawn_v {Dawn<Args...>::value};
    

/**** Commitment Separators ****/
    struct Commit
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };

    struct Launch
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };

    struct Ignite
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };
    
    struct Kindle
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };
    
    struct Prompt
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };
    
    struct Propel
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };
    
    struct Settle
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };
    
    struct Finish
    {
        template<typename...Agreements>
        using Mold = IMPLEMENTATION;
    };


/**** Regular Functions ****/
    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto idyl(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto lark(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto ease(...) {};
    
    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto free(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto glee(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto glad(...) {};
    
    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto rosy(...) {};
    
    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto rapt(...) {};


/**** Helpers ****/
    template<TEMPLATE_PARAMETER_CATEGORY...>
    struct Detail 
    {
        template<TEMPLATE_PARAMETER_CATEGORY...>
        struct Hidden 
        {
            template<TEMPLATE_PARAMETER_CATEGORY...>
            struct Secret 
            {
                template<TEMPLATE_PARAMETER_CATEGORY...>
                struct Covert 
                {
                    template<TEMPLATE_PARAMETER_CATEGORY...>
                    struct Veiled 
                    {
                        template<TEMPLATE_PARAMETER_CATEGORY...>
                        struct Trivia
                        {
                            template<TEMPLATE_PARAMETER_CATEGORY...>
                            struct Unsaid
                            {
                                template<TEMPLATE_PARAMETER_CATEGORY...>
                                struct Untold {};
                            };
                        };
                    };
                };
            };
        };
    };
};

#undef TEMPLATE_PARAMETER_CATEGORY
#undef TYPE
#undef VALUE
#undef CONTENTS
#undef IMPLEMENTATION
#undef POSSIBLY_A_TEMPLATE
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8XaYDmlCBEzEBBk%2Bfly2mPZ5DDV1BAVhkdFxtrX1jVktCsM9wX3FA2UAlLaoXsTI7BwA9BsA1AAimDQh2%2Bg%2BLACe2wkGawieWMQK2/zE28SYTOhMEXSEZwB0Jg0AEFzABmLCHTDbAAq2AAssoAkDYQB9ZRAgBKQLh2FhGJRbmR2AA4gB5DEATW2TC8REBILM4IO0xhFOU2G2wQI9LBEJZADUgQE5ByCMQvJgeYy%2BUc3KTQrCFUIpUzIdsAJIIgLw7AK5Hq%2BWcwQqmVQ5SkoRCdUWAIUlFAlGwrVEnnAgiYFhXJjukygtxOxFEtGY7G47D4wmwsmUv6x33YekTcUObbYVSsK6S4EmADsVmzwI2ACoS0WYWcElCMZgFF5aARtqWixt6ds29svCkjNsCBWob7dqz2b78yDC03tvyxBLttXa/XG6WW8D29sJt68MhtmgGBNMKoEi8aURtgA3af9vOC4UJnO7EeusdA4ul7Zwu6LkvLoGr92egw%2Bn6vaVswbCxn82D0GwggKPGrbtkmXgpsoxCoEQ760Og8Ftrmo6rquiEpkIBgKAg2H4bh5H4e2f5eoBbjAYwrCYOBQLEMAPiMAQsGggmK7UfhhENihaGoBhWF5rm96gnhAlSQ%2BBY/gJtEAZKQF9qBLGxkCwBvB6XE8XxSnUZ2wTAG%2BH4DtsxFMKRIAgCp3pmqh6F3L6hK6Zg%2BkweBcEyeR8n%2BfxOHBT2Hp0WpDEacxrGed53FwaFpnduJ2xWSJrmYe5Ol6dB3G%2BbxClPr%2B4Wqe5jGaax7GGeRyXmeJKINlZ4nZdVBXYPZjFFeRjn0RVMXadViXGWutSOFuO57geR60qgFmYSip5pXmLV%2BmxwAKO19nnt4kp3t1ikviW2zKEwwBQk234lf%2BTnuceqDgVOxB4F89A1aFQknS5qCnedy1WPtQXFTRpW3X692xblBnDaudUnWd/agoOGU/Qj2VxXlm1xoVQM9aD9EQ4NG0w%2B2cO/ZgjVpUj8Pna1G1bQ5fYHSNvWRYTfzre9I3ruN24CFNh7UrNNMU0tuHk3TWMArx20XoFo6PkdZYYqgHyfs2eM3X1%2BORf1YHYxyyAkVLHiCEw0wPCTbafSjKtq5RgMK6FrPlTr5XRfr0uG8bkNeZjVsdl25l2%2BgVPI99Ifo1DPkG8z10Ra7Wu6x7Wle9uPtE1zsNB7OqvoJTVmR2tbUG51TO487btAVXUUgQNadG7ZUucwHPObnzu7utNQsniHi3/UXhIl17su7fLAWHROGLm7Q6tXSDSeJwn4Oze16dN%2BBQiYAAjhKDBrFnCFikhwkRzP/3j4p8dldXi8r0Qa%2BNwozcY9DhVJTn090GHX2iV/tBRz9gZdqccF7LwYjXdm8Z17PyqsTd%2BI04b/wLtTf%2BksGZdQrizGuLt74PQNjA5uQ0EEETGu3SaXdBb3VnDPfuuE0HF3pqXEAO0JSXxGorCcAAxWgqAADuc9NbgNwRAu%2BtcmKe2gU/KWUiM5/AAOp1EwLcTsNZW7H2Qt9Hh/CL6O0fNfMGojhE4JTo/ORsiN7aVfjBAOcNtECPSlo3hfDAHxRkTjJ22CxEiJ8aYgh0izGWI5sQoy2czLbHsSgwc9j0HMMwZ4gx2tvEmLrpI3ihDAmwMzuojcE1%2BaUJmieSJYs8wxMYe4jqLC5Z6MUvSJWNDv6XSETfIxLSRFQPSQE/xciaioGQAAa1QqgFgh9rYaNPqJIQ58HbSVkiFLxxjkliI6d7IJFiskc2sQlEhpMc5TO/o4yZM9XGYxAVgxJuscGQNXt0tZnS5Etx2W2OG%2BzaBROssc8pGDy4JLAW0q5yybkN3MfcoJjzQlH1yR3AWhS5qvLoXmV5sSR5VLHjUp8dSJxCAYDopplclmLMJW0vxwK7mrI2esqWQgSCoRcU80ayYJlEGxTomZoC2w%2BIBUSwxetU6UsyRUjJVjo7bIhc8vZOKHHUxRiyulHkRUVPZWFAl/yVU8pJfy25FLQUbPBbVCV/D3myuRfGMulYlWcrVUk4RGqdWCq6aS3VITyJtzyZ3fcVDhayoRRYY1XzmGsL2rMx8mLXwAAlz54oWaq7l1qWkrKFY6%2B1ci4RtEMMgW4tAzjqMZb/IgEaDmSXRauZpPKuUxvjUCzVSaBW%2BzcbYnOBbZ6HPzZ8%2BVQCY5ewteWstVq2ZVrtbWrVRD4FisDuEpt7ym0mplozc15y/m9tjZcwFD9h1Dprdk%2BlrroUFJ7nNSdJSLDTv9SiwN7DOGvg8J4QR%2BLl1LwrUu4lqS%2BWDvXe%2BzdfwhB0EYGsHNJ882oGvc2otwar6LrjU%2BqDkG%2Bq2vJcmslibq05Q7aK/V4TgM/xRsBk5wDY4Lo5T2mDK773qRfRu6tlG33BNHeh7swH3k4dPaaudalfmEb7Q%2B6DJHn0SNffBij1HkPOo%2BmQt1ML93bAY0epjQ8mFnuqWBjF44r1iBYLe6N3GuPEe0/2tdn6qMCY/dCYghhd50H/Zo0Sbg1O6KU6WnTt9SOtMMQmh1hmkPUZQ/W%2BlcMbO0HUy2oDancOdr8ux5VznLXObcyCozBmvMicQTnfzLBGMheY7O%2BJ%2BiIM8a005x9BMB3xY8%2B5xLtHRNQooR62FUm1M%2BtSzOyp570WXuOsSZ6DYo0XN071gr%2BWXOwfIx%2B0rcXPPxdNikPc%2B9s3bvGYBjrhA7Pds4/1xzg28tDb44JkrQm9vxe8/7XzOdFtNWld9U7oX8r4Yi9Fwrm2Ht9fEZVEb%2B3xvvYdXqj%2B4TTvvMu5lyp2XwMcai0Rx7a3k7DYS7tmHH2HlJdIVV/JNXJO/aPf9uTFTR5sNa5PV88i6Cz267lp7d2BvtOK3DxDZXYcOuUNEJQp5ojprUmOm230Ce0BAwDezd77uk7B092L1Oxs06p7qrZozx3dk58287olZdXcVQRyL/OIcC9WzZynYudei712ChHuzwmy/eYrgHZq2M5ZB2rjbGuYva/19q2njuR1S53dV7u1CTdHrN5jhmLXedPnqcSZxGmevq4j7byPZOtsveh%2BLhDTuE%2Bby8LuBA0w3fzZRiH1loGVug81zH8Hz366jZF%2BXpPuuwWS4bT90PQWc9ysO3hrtKui925t%2B3sj23XvO4r4ngfcCpdw0b395xTWLf5874L6PM%2BS9pL75Xl3O3E1fe5mJ3dKPqGj/R%2BP83qKceB9DcdXYTA%2BEMDDyT2fhe58U/02Xpf/eV8OqEKn0iGfLNMtQKf8/y22%2B34AJv1XXwXjyr0f3AMH2FVQ2Hxzh/wvyCzgKVzOVu0AILzQMrXvzezAMgNAPhwq2S3CTgPeUQP3yB2Bmt3J1QOn2AOf2X172Ty3TZw3w909RPCIKPRIL9wDUUyKhLTx2Og8BYBYEIDymskwASDqG9BIEeGJzGVzUEOEO5FCkolCnD3n1TmbxsXpTCRSksmpk1ERB1D1GhANFCF4PbAvVE1zQCBpH3jImUMklUKv3ULrSOzHR0Pqj0MHAMO1BxGMNMPMJwlx3X1zXVGAAYEICzA4UcJGjUN5VcLfncKN10Mwh/h8KMOhH1HlECOWiUz4JCIAwAGlgh0B6AAoYiBJVd1UodNC0MnDxVwlUorJ0i/DMiTDsigYS1i0LCrCAMRJPQlDoi5l8JfEaia9tDkjPDUjmitQMisizDOiLDuj5lSFc0RJKwAEHDhi4iSVaipcPD5pQ4ZjDDWj5icj2F8jViAMt4CACAyitiqJnD4ioCfMkiGiUijj9DZjTj2iFjhiLieiCiUwuFgg8BSJyjtinjdjxi3jpcpjPjvDvjdQ2iAjFigij8VNjpqwOIDAXguFU8qh%2BZL8KD6IAwkRUR0QsQcQ8QCQiRowKQQFKteZqsdpJM8B0AzhaAIBwJ5g/8UCxEySgxKTQwaTIwSRyQGTY4mTyFkdWTqFcT%2BluTYxeS2V/8BT4RAwKSQxqTwxaSowJTGT18kd3U5ThZ3glAlS/gVS880S0o%2BdDFBStSqSwwIw6SDSpSjTmTZSxBJMqA9JLTrSecp8HSNTyTsBgxnTRS3SYwPTEcvSTSfTqFgB6BMAAy%2BSrcqjSTQyhTtSXS9TxSYyu1pTxN3RTSTxkyPg0zVT/j7SsznQnSRTdSxT6TDS4yZSEzZ5qFUIFAzgqybSazNM6zNTwzhSdTXT9TCycl4y9wyy5pTMEgCA%2BygysFj8yww02hKwHhiTMzIpHSRzcyoyJzJSiygSGx9hagDkHj6idz3I9yIzGzxyCzjyA4riUww12SsB4DryVDYjlIa47zRy8zmz3STzKjXyGwt5kA3gmpryujISwKby/QAKDymzoznyJiELPoPAmd6g7TfyEKfyEKEKRFkLIzUKjzWyiLKjPp%2BRMAf0jjYKiLCKqKiKSLsyGyxz8yWzYyWLML5sTM8BTwXpHjeK4KRLRLqI2L6z9yyLHzuLQKJKiLPo5BdxzYsJGLFKL4NLNLnDSKHyuKQKXydLqL5sVKiBpj%2BzxLjKATjL0SciJKbKWLHLKjnKli8i3LupgiwRU8IQYR2KZL9LgLKQVQfKDghwjJvKGBfLrwRQQqoqwq5QFRkTlRsxGRQqqANQkT/DsjUrQR0qToLQrQbQ7QHQ9yOBFhaBOAABWXgPwDgLQUgVATgNwawawNcZYVYfsRkHgUgAgTQcqxYfpEAKqjQP4UEKq2IWIUEMwAANg0Cqq4FBA0C4DMCqv0E4EkF4BYAkA0A0FIDqoaqao4F4AUBAD2r6vqvKtIDgFgBgEQBAGWAIASFpHIEoDQE9B/WIFCGYk4FUFiBmoAFoZrJBthgBkAtwpA/gzBeBMB8AiBnp0A9B%2BBBARAxB2ApAZBBBFAVB1BLrSBdAWg%2BF5zOAeAKrqrar%2BrGrOBSRaRnqGxUAMq/rAbgbQbwbthIazBtgIBBCEhPq0pur5heALqtBFgIAkB3reb6AyAKAIAJbPqQBgApAzA%2BA6B3QHhKAIhKbvhmBiAzgSbeBta6gzhSQIhtBKgLqer3q8pSQGAs1KasAIgvBgB/NaBTruBeAsAWBDBkz1gGr8A3gqgmc3aGr9xKhaR1gequQ2hKbaA8AIhTNdaPAsBKaxQ8Btr3bSAcKIhkhMB9gvajBY6jB%2BrFgqADANp%2BQ8BMA%2BFSQQJ9bMbhBRBxAMbkb5AlA1BKaCb9BvaUBWrLB9A47TrYBNIQBs7kgCBM6BhuB/qBrGqFy0g3aAaJgsIkZTBLBrAzBDqcKEaax4BFgKhCS/AIBXBRhmhSBAhpgigShshkhUgBAT7r7cg0hehL65hWh2hqhJh77xg2hzaP7uhn7%2BhSghhugv7gH6gAHZhSg96Oq1gJAyaOAar9rKajrtgmagaQawaIbJAoaubcBCASB%2BbQQuBBberi7FgEB3h7hKBBqQBJBQQ/gABOUEHMSQDQSQMwSQOa%2Bamahh9ajgTa0gbaswBhv4WITh4RjQGaka1hqRrgGapBvGo6k6s60hy60Wu6sWh62ml6mWuWqW76tgX6/69B9ebsLgERrgP4EOuGkgdkpG2QVGpu6QFu7G9uvG3QZWompgBIfW%2BBxBg63gI6mmp62kbYBm1B4xlmxuMxixqxrmnmvmsEMwEh4Wq6zRvR6IV62W4ZSWgYaJxWhhrgPamgesBnDWrW4II2uuw23Wk2s2hwOuq2riG2u2vGh2p2l2t2nqz2728QNpvAAOxwIOym0O5AcOuuqOyqvG2O%2BOo2pO32oW56dOnqrOnOvO3psyYuvgMuhQCuqumuxgOuluxx9G5x2QVx3Ghqjxruou1eqwPumZweqAYe0eiYCemIKemame1AOe/mTgReggZe3YO59eze6Ibep5ven%2Bg%2BlwKK0B8%2BwoQBh%2B2%2B9ITwJoZFjoCBq%2B7%2B9%2BgQLoEYNFsYN%2B3%2BvFyYLF1%2B9cAlzIU%2BylqYRFyBuBpYFYWB4hvh/x5BzgCJ5mkG/J9m2JjQXBmxl4MEYhoWsh0gChj4AYCAeBgR7a8aqxnMGa2IKqzhlhnMBhmanMKq%2BRgJqm462wFR1J9R%2BATRx6umrJjJr6n6jgVQFmkZU8LcU8cxv4VSCYGGoVuxloY5xu05%2Bui5jukAUEUgLxnx92vximxR6m7R%2Bmxm%2B1hQR1s8F1t1hsbmnJxJxkUEFJrZ9J9NqWy1vNgYR1hIBIRacxlEFNlEO15x1WspiATWvGmpvWjOptup82xp4Za2225tv2zAR252sQV2uunpguhZ0gf23%2B4ZvG0Z8ZjOyZmOuOhOs4eZlOpZuu1ZpQdZguzZtR7Zs6XZyu6u2ujOn1tGiQM5rGtuy5nQINm54wXumwR53e2ejoN2jYJenuteywDewJre9kneyAKF3Fw%2B4%2Bwl0%2BhFmYbFxIG%2BjoUBnIFF8loB/ejofFhoMDvQZDv%2B8Bi%2BpF8YT%2B9DvD/%2BnDhl1lhQGB9GiNhRw6zl6t7YB1p15NpyCYQV/B4VgWsVtR8hyh6V2VraoNqqxV5V1VrVyQDVrVnVqjwJzgZR868VoayQER4GrgORnMUEBhyQf6hh2IXhqZ0ESN6jg141%2BB6GyT/VjjkWxYHClIZwSQIAA%3D%3D)
