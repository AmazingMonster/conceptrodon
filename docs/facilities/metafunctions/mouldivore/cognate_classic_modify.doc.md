<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateClassicModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-classic-modify">To Index</a></p>

## Description

`Mouldivore::CognateClassicModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Oper
-> Transf
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;::type, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;::type, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;::type, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateClassicRemove
 :: template<typename...> class...
 -> template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateClassicRemove
{
    template<template<typename...> class>
    alias Road
    {
        template<auto...>
        alias Page
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>` and invoke `Operation` with the result.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinus
{
    using type = Vay<-Val::value>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateClassicModify<Operation>
::Road<UnaryMinus>
::Page<1, 3, 5>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateClassicModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyTypes`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateClassicModify
{
    template<template<typename...> class Hormone>
    struct ProtoRoad
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...Elements>
            using Mold = Send
            <
                typename Send
                <
                    typename Pagelivore::CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::ClassicModifyTypes>
                ::template Road<Hormone>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIGSAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutwhZkCEWQ3iwTxMgTcXkctEIAE8kdhIeYYQw4V4EUi3MhFugsFRsbigecnspiJgaKp/mdwQRMCx0gYOSSCBiPsw2KQnkxUahqfc0AT3gR6YzmYjAi8ngRiF5MEirPdIcDjk83Ex0govPRWad2ZzuUxecj%2BYLWJgAHQuyV3RbqhwGo0m%2BhamkPOnYVQchjoABixFk5uukI5XJ5mrtAsYjrdHq8XuDoYjUcEiIA7FYCy9/Tr7vHrba3JXE3yU0Lna7AtgnnCmAo/h5BEwVmRVQ3HS6ndh6GxBAp02rM3Ls65I7ISd3Wn2SaPOYwCAph9SW7ii5CnkfVVa68mHWxhxZMMAIgwIsBJ3v7senl5skYngBZTzoJUq5de0iYgSWvW8GHvIxtxdEV13HLcdz3QJtQhEsywhCtTxtJMayw6sxSIRDW3bTsniETAAEcNRlEUCNQYcADU2jwJhYnoJ8cXuDMsxDec8wIElyKor4cKY4gWLY34iLdEwDxfY9a2wkk6KvG87wfDjD2Pd8H3pJhgEwf8yMo6j9lAtSII04cRTEiT2Ok5D91LRzy0DZ4AHlx3vAA3Eh2BANwDE7PBkB/fAqAxAAVFM/gBSFGwUdImH2J5PMYHy/MLFC4zwnD7VTS9m0491py9QKO2yUKMDwCLoo%2BP5ZOLZzstpZ4LA7QzDSUGNLQTJTkRUl0AEkp09OVyuCqrwqimKSXJEAQAiLBVAAfSUYSZRJIaHOKxqtKPRTq0OvLB0Kp1sTbIK/ncj5iBtXI3Vfbi5QZVAiAAJVQJh0H2rLftfY7/uPEkgdfA7TsMyK2gMghSFBsH8sbK9koAazuYhH3hx6waPRZ7uQNsBEWTBvLEUVxSePB0AxWh4YgeHX0OQ4nmDJKw0RFINAZJk8FULbsR3TnVVQQmvHzaGfE3P54n4RlVQQQyZhh875Jx19ueZfmW3JwiXSofiVuhhQ4dVtWjyZp5IruhgFFllh5cMyIQ1FDHJcEFW7jN18oYxzBYYZ48LfyfoHaeRlFg9r3j3a5A0Yx6DI7VjZ4YAWguw1jVNTVTdfEGc7VxHHSeLA4Xy6gDaNjYFvy6yA/Bi9DJuhJ7oEesG8t6G/erlNsW7j4Tc9qOB3bmO48fPum0TnHdxaweccB88Csnu5gEZDcJ2xnGdM/H9aD/JEVRL2gy6pmmIHmkB8pWqnN0xEkV7X%2BDNIPEthw2ZOXLnwtmoDAHcr5f%2Bi8kZFUuhVYcD9MDry3JvN8H5gBPE%2Bt9Iyr0PpfR%2BsiCBUCE4zycuhHKfV8LimHENWiRCXQAClRozgNFdEKYUaozXqnNAg6AFpLUwKtdapkcLbSKiKC%2B7DOEmREiSchO19woT/gQvKgCawQyIqA0iTc7oDBgc9eUb1UCIJ%2BqbPa%2BcDr/30UqNwddh5LyeOGPAxBFg%2BxhgPIeZjGzGWlOgWxft7FD0LmdUe6NMZGJgU9VojgCbSmJqTWgOsRan1pkY%2BmRjGbM1ZoYfenMNa8y1tgQWGhhai3Fq7J%2BTwZaZQIArJ4NBrFyiVn7KeXs0l82RCNbWg0nT61kIbeOHio4WytoYW2JB7YlMdhwuUEt4I1LNpYipbj/bxMDok1QbMUlcwVOk5ElCWxZJycAEWyUoykUGcXPAeMZSFL9gAd0gQwVUZyRZVIQqYupoiLrNJYFTdA9B2mPk6V7bp1s%2BnEAGaUp2Iz8mbnGWrciLjpnfLNkHTwIcDnhwIOCnGPj447iMcnIxadtYZ19NnL%2BudkSmK8YZI%2BZdWmCE%2BQoKul8Uy11mfXcxyiW4MDbuYyZNjO4EAnr3Ol/cSUQ2Lo0Y%2BKYICvIpB8yuE8GWEoLkKllqigFF0hQIVx3LeUtgnjC%2BVI9Ua%2BIUDK10/ikKzzNgvORDdwGr0gU/AJ2k4Hfl/EZclYronnxYRPa%2BWBBB3wwTarB1IX4vDfh/SRwM0Kf1%2BhamN8iQEkQTpgu1z4v7b3gdo5BUZUHfXvgGp%2BDlsqRtnnqBBjRdjZG8p1DqPV8FVhws0khkThzkJFKS4c7lBnECEtwzSXFSrjVoVNBhdVfjMNYYtMMHC1rCM2g0oi/DPUTuWtOjaZk1nztSp27tIlsEpr0V/GNsi23xquqlW6rK1H9o0dmnRX993msMXKo8ecn0IyFZygg0LBXt1VWGL9jLHFDhdGivxr77W4yCSFQmNsOThMiZTamMTX1xNfQklmCzkkc2WTzepbhGmZNdELIguSQXADdluU5stFalPKYsVU3KUVg0eQ055ZCWkVw6aY35vS7ah2BS7MjYzTEfv/ahuZ6HFlYeY24dZBHzpEZFts0UyA9l/AOfgY5KV4gEAuYwa5tzuXbgeSs3Dsmm0ugle8zA1KdU424zbXjBz%2BOjLBaY396rfYzLE%2BbZmwdGiVNKUixjr4QPYMxanC6c4wwLkEFjYlAHXUfFMShhxr4JqVXobVWayIO0Ky7TO/Yu7iqpePNXXKCC0EkkVQ9FNJWjxsMQxAULe1X4uixd5p47WzbgaeGV6RTq95xZMQB0lwrS5ispQQaltKa4wW/cy89SrLUcqsVyzzmrsDavm04xLmBxVvKlfHGb9K5sjYVYtmry2nHuemRt3lJqcRRqMbGq1Lok1Sx62mgb%2B9lRjdFR8CA7qL5Xxvr6/kubH4fb3MG0N6Fc5Ft/gpI9R643nW1gm61kON61YdbpDNB9r1aMq/6rHCEip4IR65WSpZXIlqEAgVEBAzRxUwtI5SbGqFenp4zv0T23KnCeGJDEsQ8C%2BUZAtOqIUxDKFQOkGt9wEpJRSkLkXYvDL7trWeQ0HOU3qMl6IWgMu5ctZ/q5C1dELGrYErrq9%2Bvpey5JB%2BmSclU2OvykZbnBAmc4RwTqSnGE7jm4ph%2B0hxH3Oc7lHbw3DvkQh%2BcWq534ajxffdwTz33vHdW996hU3Aeg/Ebjxb9zof6IulywkXtJUxqWwFFL6P6RM8VJFMXzdeWisSN%2BinnuujftRdzIuZVbAa/pDr0bqrnaisbd%2Bn1utekDKN8WM3xoCfTW4L59TgMdPXDy8Dyj17aPirqPIuzE3eDWd1oAWzgaOviKnu3TRczTpbKsXYhH4yYZBIFdEsxF/Ulyd7pdykQvztFkWaQugTTPWbiVWK2PHUTeBXCQ3hyTzBi7w%2BCMmq1bmRGf0knb0/nh1z2jWRyv2111gP0UUTTzShxgOT0dXel7AiQJ3gPoIh1tSliIk1ULQIPPy1xeyXgUQgMAj7FbVRzgioMhCP1cCXFkCAgSDXDHDYP/12kAKR2IN4OATIIgIwLZRxwg2ryYLoF%2BnvTVlQPV1%2By0LkKwQLUMP90INUL3z4JPTATe0oOx2oNgTxzQSMn0NphJ1YInHYP5STE4LP3531GUH0j6FFz8gWg8GAGYA5HImAHgh30V2SkMnCIMnRDVz%2BjNyIOAJINLw0NPXMJt2r1iPiMwESPgg71NgtWyAAC9rM5RG0Gimjm1L09C/ZmDdFlD55ZFWiVpkUXQABpHrRkKiKxX4J4CAHcMwFIcwFICAYY4xJ4chd%2BeGL7AACTeUYEGPQIu0wLwxFHIRTmGKsJ6K4IPVALY3e1cM70dQyNMJVGP3QSuyLhVyiPFxACjzH18MsKKin1Nhn0TAQWYORG8JYP%2BIP2BOwieG2IpF2Ot0e2LWZiGjDBCimNECuTEAUBFniCeCSk7EwD/C%2BxME5gEUnSEVXU1E5hqTULTB0KeHUXhJ9T%2BhsNqP6LwEaL2JaK5LaIoQ6OoRZMYDHTYUpJXW4S2mOPER6OQKAK1wGKGKdFGMZNfHGK8EmL%2BBmNdDmIWKWJWLWK62MMdW8L2IJxKKONWNOPOIDzNhMI90kMH0Mg%2BLVwl1rwN1%2BMtLEQBMCJ6xhI5FBIMPBK6LoEGOz3wJCPlP6jeLOluOgUZK%2B13h%2BxVGFO0LcDjMn19KjXZJz031BHzLBF1DpCGgTCgVZR3z1ALNBHBE12jPpLOnAOKIOO0MPyvXKOwnSzoWqgihqKuLsNUNR0bIqjhP6QECTDcPURQSJxzVlPhjqL5J5P4QXKVNkw2JNJDNoDNN%2BzxSzlFJABYCYBRms0EQlJERYxbAXXHQPKPOvnFK4TPJkxTi4AFn/zNQLk5O5KVPw3hknKzVQEeKxl6K9nrMnlELuIA0TOdTT0kIAxfTq0AyHxeNMSJWGw63NSFUeKyOiIClQDiOwiqM3BJFNKROQrVn9PSIiK2mkgAyJU20vnK20Sqy8k%2BP8k7KHSyyYVVKHnIoqxzWRE2NHMiB6zNh4qTIsPzXJ1gq4pxh4sYpy2bPDLVg3z5wfWIOaQzM%2BweIiMzU0QAr%2BIkoPzhwjUuKjKOnsPUKHM7Exz8PjLcK%2B3x1%2BynLkvTJcLJ0MuzMuMrKrPBBLWDFYG5EMhZ1CKrNjCp2hFhHhFMNJAEH2HSFsrzOeCYgxB33zxFm/L7WrySokSZMgxCSJg5AWWIHg3CQ1CyhGiLW/hCJLTkGYGIAxC/AiHfBSvMveLEDfxqraHqsasnD92QPtIJyyuRBTiYloAWhKvHIp08rpC0OaoHP3zfxKOLTpC/C6KoDFiaAEFmvyOPSdANTdETNWvWoGCMnbI5DYsyyxHkqgJq2KgWmco6rqoaoYHfDdAWj0rcC4BFGCCeH8FepADEowXRVfISoFyEC8HSBKGJPel%2BFNDlCCq%2BzBohqyChphuPn2OusOMGrcA0GxBsiYEurcCfNxsF3xpJDMGJqxpTkCAptJuREkBpoJpTl%2BqQmRJBv1Ght9DhrZEhHstRrlAJxWtaDWoJCWyxpxovJJoJufIlqxvJpltprcGpvloJvpuVpJGZse1ZtpzpEil%2BC5otHENysNiJPaA9XHQUEdGNpJA5thub3BshvQBtuPmxDDQ4C2FGo4H8F4D8A4C0FIFQE4BMUsGsCZJ2D2HV2hB4FIB5V9rdq2BRgCEkCdA0AAA4zAzAABODOrgfwVOlOrgAsAsaQD2yQXgFgCQDQDQUgH2v2gOjgXgQ1KumOrQLYOAWAGARAEAHYAgdIVEcgSgNALkOgBIKIR0TgVQFOlIFOFISQJ4YAZAAmKQJ0MwXgYkwgEgKmPQfgQQEQMQdgKQGQQQRQFQdQWO0gXQT6s5O6dITgHgd2zgL26uzQXgOu9yVEXuuUVAKgJ4Ceqemeuehep4JeswaYjwIe%2BgIqvELgDYXgZut20gCAJAQekfCB/uiAZB4exIYAKQMwPgOgDkaxSgWIZ%2B0gEXWqjEW%2B3gMhzq9yWIbQfzSh0gQe%2BCdyBgWgChs%2BrAWILwYAQ0WgWgQ1bgXgLAA8owcQThyYpoStQRv2jhMtDkRhiIDkD2v29EWIO6OqjwLAEhtUPAcuoR0gStYgWIZGt4UR4AdEIwZ%2BrYKgAwR8BiH4M5JuH2qO7e4QA3fe6QNx4%2BtQEhi%2B/QQwYwawawfQPAWIQ1SALYWXAYQRlOckA%2BUwYOywMwWuox8SLACJiALYBoDavwCAVwOYPwT6sIFYKoGoPQEoHIAQQpiprIKphgUYMpiYT6nJgYIYWYTwLoPQVp5oJYRp8YRIFppYGpoZ4YfptYQZ7JsO/YCQe%2Bz272khuun%2Bye6e2e%2BexepOkBiAXAdeyByOmB6O6xrYBWb6CYLJ0gBOyQQIJ0DOwIIujQSQMwVISu/wFIDO/QTgUu0gcuwILgJ0FILgFIFOjO/OlIfwSQHO25tIGul%2BzgBukAJu6xhBjuxBru9%2BvuigdB1AcBkesejgNoFgbyAsFOJgUBT8LgDOp0P52R/AIgdJre2QXe8QA%2B7xpQXxs%2B3QXBq%2Bo0ShuZx%2BmF/2zgN%2Bnu1EJ4L%2B5Zv%2B2e9sclyl6l0B7FlBhIREaEMwA5uB1upBhVzBtBjBiBlAAwIwClrgKumgY%2BCvIhkh6huqxhq1jEWh%2BhhwRh5hzcVh9hkhrhnhvhgRxhkRwJ8Rv2/ARkKR34EhuR5AVEA4KOpRvoEhtRjRjELRg4P23R/RqOoxkxpQMxv1h8JF2x/SBQBxzAJxwURhtxplzxw%2B%2BQNl0%2Bv2zlgJqxxJqwSwUJ8J%2BAKJuK3IWJ%2BJ5URt6wFJl%2BtJm%2BTJ7JvofzXIFwMMEZkIMMcZ8pz6ypgYKdhd3IWd5p3ofoXp4YKdnpgQdp5YSoAZ7p4ZzpwoUZ9oVdyZ7YXYGZ6Bj5%2BZp%2Bs%2BpZ3%2B1Zsl%2BBClql5O6YnZul5V35tVo50gE5rARIc5kusupISlh5gsfwDOwu5IJ5mez6gVuu%2BFxF2O1ulFpAbuj%2BnVrViB0etgTgAl/%2BlgBQbyAmbyd9xMRYVe2lje1hT6stjxiQLx2QHxmtnQJIUgblm%2BoRvlhZx9oV9Fz%2B7%2B1QEjsjijqj7COjCAMBxVvZwIQIf99DhBzVnFsgTF3ViYcjiGlaSjjOlaajqbMTrx/B81iAYhs%2B21m1iIGhuhhhgx51wQV1jhgNzAbh3hsQb1gx31sRpN4RyRxwaR0N1QeRyN3gaNlR3gONzqxNnR8SVN3gdN0xzkbNqxlTvN%2Bxxx5x0txl5jlltj6tvxrjg1oJpJmwNR4d/2jtomTgQ4eaXt5J1JhIdJkNyJ9dsd5wfJydk9op6d9AC92p0oXIJdupgYQblp0d3Jvd7dqbtpvp0pw9s9joXro9sZxbiZ2Zq98Orbj2/lxZzgH%2B8T8jp4fTp0Izr9ujhT6B2BgDoDs5uZr58uzOp0RT/wXOiFyuxTgsIFh92uuF2wBFw59D%2BOkASQfwG5gugsSulOyQbOrgNOuYu9wIAT/7%2Bu4HluuZlev72F9H9VrYIx7IZwSQIAA)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_classic_modify/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_classic_modify.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_classic_modify.test.hpp)
