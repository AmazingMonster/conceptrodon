<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Vocabulary

When I choose a technical expression to use in the documentation, I first attempt to keep it close to the relevant C++ terminologies since they are well-documented and familiar to a programmer.
However, C++ terms can be confusing. For example, it is unclear what the 'non-type' in the 'non-type template parameter' refers to, as it looks like the complement of all 'type template parameters'.
Moreover, the term 'template template parameter' not only repeats the same word twice like a typo but also erases the differences between the parameter lists within template template parameters.
The detection of the differences, however, is the key part of this library.

As a result, some vocabulary used in the documentation will have meanings unique to this library.
The goal is to maintain the usual flow of written English while providing insights through the selection of words.
Strict definitions for conventional programming terms have little practical use.
They are there for the convenience of authors who try to be as accurate as possible.
Understanding these terms shall not be a burden for the readers or users, as these terms shall be used intuitively and conventionally.
This is what I want to achieve.

<pre><code>// I didn't know what these things were called
// until I started working on the documentation.
// Yet, I was still able to use them in code.

template ---------------------------------------------------+
<                                                           |
    template&lt;typename...&gt; ------> template-head       template-head
    class ----------------------> type-parameter-key        |
    Arg ------------------------> identifier                |
> ----------------------------------------------------------+</code></pre>

## Metafunction || Function || Operation || Vessel

In C++, the word 'metafunction' does not have a decisive definition and often acts as a synonym for 'template'.
In this library, the word represents a class template or an alias template, as these are the only kinds of templates acceptable as template arguments in C++20.

The goal is to define the kind of metafunctions this library focuses on. To start with, we will categorize metafunctions by their primary signatures, where a primary signature is defined as follows:

- <code>typename</code> for a type;
- <code>auto</code> for a value;
- the template head for a template.

Namely, primary signatures extend the notion of template heads by two special cases. Now, we will define the conformed signatures.

## Container || Sequence

For example, I use the words 'container' or 'sequence' to mean a template whose job is to hold its arguments.
In this sense, the two words are interchangeable.
However, I select the word 'container' when the template holds types exclusively, meaning its template head is `template<typename...>`, and the word 'sequence' when the template holds values exclusively, meaning its template head is `template<auto...>`.
This specification is beneficial when both of them appear in the same context, where lengthy quantifiers must be applied if a single word denotes multiple sorts of holder templates.

## Element || Variable

Another example would be the use of the word 'element', which denotes a type in a container, and the word 'variable', which denotes a value in a sequence.
Honestly, I would like to write 'type' instead of 'element' and 'value' instead of 'variable'.
However, both words have been designated as the conventional names for type traits by the C++ community.
To avoid possible confusion, I adopted the lengthier ones.

The word 'variable' is inaccurate as nothing varies for a non-type parameter.
Other words like 'datum' and 'member' are considered.
'Datum' is rejected since its plural form is irregular, a significant setback as it prohibits Find-and-Relace.
I prefer 'member' over 'variable' since the former often denotes an element in math.
Yet again, the word 'member' already has an established meaning in programming.
It commonly refers to a component of a class.
Therefore, I rejected the word to avoid creating a mess.
While 'variable' is inaccurate, I doubt this inaccuracy will become the source of confusion, and its resemblance to the word 'value' also gives it an edge.

## Layer

Another example I would like to talk about is the use of the word 'layer'. An illustration might help in understanding the term.

<pre><code>template<...> ----------------------------------+
Metafunction                                               |
{                                                      0th Layer
    template<...> -----------------------------------+     |
    NestedMetafunction                               |     |
    {                                            1st Layer |
        template<...> -------------------------+     |     |
        NestedMetafunction                     |     |     |
        {                                  2nd Layer |     |
                  ...                          |     |     |
            template<...> ---------------+     |     |     |
            NestedMetafunction      Last Layer |     |     |
            {}; -------------------------+     |     |     |
                  ...                          |     |     |
        }; ------------------------------------+     |     |
    }; ----------------------------------------------+     |
}; --------------------------------------------------------+</code></pre>

Each layer is a nested metafunction, except the *0*th one.
A layer's number suggests its position in an invocation order.
To invoke the (*n* + 1)th layer, the *n*th layer must be instantiated first.
This rule applies recursively, with the *0*th layer serving as the base case, which can be invoked directly.

## Contents

<table>
  <thead>
    <tr>
      <th>Vocabulary</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>metafunction</td>
      <td>A metafunction is a class template or an alias template.</td>
    </tr>
    <tr>
      <td>signature</td>
      <td>
        A signature is:
        <ul>
          <li><code>typename</code> for a type;</li>
          <li><code>auto</code> for a value;</li>
          <li>the template head for a template.</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td>conformed</td>
      <td>
        A template head is conformed if one of the following is true:
        <ul>
          <li>
            Its parameter list only consists of type template parameters(<code>typename</code>);
          </li>
          <li>
            Its parameter list only consists of non-type template parameters(<code>auto</code>);
          </li>
          <li>
            Its parameter list only consists of conformed template heads.
          </li>
        </ul>
        A metafunction is conformed if its template head is conformed.
      </td>
    </tr>
    <tr>
      <td>function</td>
      <td>A function is a conformed metafunction.</td>
    </tr>
    <tr>
      <td>category</td>
      <td>
        Let M be the set of all functions, define &sim; as follows: &forall; (x, y) &isin; M, x &sim; y &iff; x and y have the same signature. Then a category is an equivalence class in M under &sim;.
      </td>
    </tr>
  </tbody>
</table>

<table>
  <thead>
    <tr>
      <th>Vocabulary</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>vessel</td>
      <td>function that transports arguments via its parameter list</td>
    </tr>
    <tr>
      <td>packed vessel</td>
      <td>instantiation of a vessel</td>
    </tr>
    <tr>
      <td>operation</td>
      <td>
        An operation is
        <ul>
          <li>a function or</li>
          <li>a type with a function as a member.</li>
        </ul>
          The word is used when the focus is on the function's functionality
      </td>
    </tr>
    <tr>
      <td>list</td>
      <td>arrangement of tokens where tokens can be enumerated</td>
    </tr>
    <tr>
      <td>type result</td>
      <td>class member <code>type</code> of an instantiated function</td>
    </tr>
    <tr>
      <td>invoke</td>
      <td>instantiate</td>
    </tr>
    <tr>
      <td>value result</td>
      <td>class member <code>value</code> of an instantiated function</td>
    </tr>
    <tr>
      <td>layer</td>
      <td>A layer of a function is a member template of the function or a member template of a layer of the function</td>
    </tr>
    <tr>
      <td><i>0</i>th layer</td>
      <td>The function itself</td>
    </tr>
    <tr>
      <td><i>n</i>th layer</td>
      <td>A member template of <i>n-1</i>th layer</td>
    </tr>
    <tr>
      <td>invocation order</td>
      <td>The invocation order of a function is the arrangement of the function's layers</td>
    </tr>
    <tr>
      <td>finally-returned function</td>
      <td>the last layer of a given metafunction</td>
    </tr>
  </tbody>
</table>

<table>
  <thead>
    <tr>
      <th>Vocabulary</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Mold</td>
      <td>
        Function with the signature <code>template&lt;typename...&gt;</code>
      </td>
      </tr>
      <tr>
        <td>Page</td>
        <td>
          Function with the signature <code>template&lt;auto...&gt;</code>
        </td>
      </tr>
      <tr>
        <td>Road</td>
        <td>
          Function with the signature <code>template&lt;template&lt;typename...&gt;&nbsp;class...&gt;</code>
        </td>
      </tr>
      <tr>
        <td>Rail</td>
        <td>
          Function with the signature <code>template&lt;template&lt;auto...&gt;&nbsp;class...&gt;</code>
        </td>
      </tr>
      <tr>
        <td>Flow</td>
        <td>
          Function with the signature <code>template&lt;template&lt;template&lt;typename...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code>
        </td>
      </tr>
      <tr>
        <td>Sail</td>
        <td>
          Function with the signature <code>template&lt;template&lt;template&lt;auto...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code>
        </td>
      </tr>
  </tbody>
</table>

<table>
  <thead>
    <tr>
      <th>Vocabulary</th>
      <th>Usage</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>warehouse(s)</td>
      <td>parameter(s) for a Flow</td>
    </tr>
    <tr>
      <td>stockroom(s)</td>
      <td>parameter(s) for a Sail</td>
    </tr>
    <tr>
      <td>container(s)</td>
      <td>parameter(s) for a Road or a warehouse</td>
    </tr>
    <tr>
      <td>sequence(s)</td>
      <td>parameter(s) for a Rail or a stockroom</td>
    </tr>
    <tr>
      <td>element(s)</td>
      <td>parameter(s) for a Mold or a container</td>
    </tr>
    <tr>
      <td>variable(s)</td>
      <td>parameter(s) for a Page or a sequence</td>
    </tr>
  </tbody>
</table>

<table>
  <thead>
    <tr>
      <th>Vocabulary</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>packed warehouse</td>
      <td>instantiation of a warehouse</td>
    </tr>
    <tr>
      <td>packed stockroom</td>
      <td>instantiation of a stockroom</td>
    </tr>
    <tr>
      <td>packed container</td>
      <td>instantiation of a container</td>
    </tr>
    <tr>
      <td>packed sequence</td>
      <td>instantiation of a sequence</td>
    </tr>
  </tbody>
</table>

<table>
  <thead>
    <tr>
      <th>Vocabulary</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>typelivore</td>
      <td>A funtion that feeds on types</td>
    </tr>
    <tr>
      <td>varybivore</td>
      <td>A funtion that feeds on values</td>
    </tr>
    <tr>
      <td>mouldivore</td>
      <td> A funtion that feeds on Molds </td>
    </tr>
    <tr>
      <td>pagelivore</td>
      <td> A funtion that feeds on Pages </td>
    </tr>
    <tr>
      <td>roadrivore</td>
      <td>A funtion that feeds on Roads</td>
    </tr>
    <tr>
      <td>raillivore</td>
      <td>A funtion that feeds on Rails</td>
    </tr>
    <tr>
      <td>cotanivore</td>
      <td>A funtion that feeds on packed containers</td>
    </tr>
    <tr>
      <td>sequnivore</td>
      <td>A funtion that feeds on packed sequence</td>
    </tr>
    <tr>
      <td>warehivore</td>
      <td>A funtion that feeds on packed warehouses</td>
    </tr>
    <tr>
      <td>stockivore</td>
      <td>A funtion that feeds on packed stockrooms</td>
    </tr>
  </tbody>
</table>

<table>
  <thead>
    <tr>
      <th>Species</th>
      <th>Host</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>typella</td>
      <td>typelivore</td>
    </tr>
    <tr>
      <td>varbola</td>
      <td>varybivore</td>
    </tr>
    <tr>
      <td>moldiae</td>
      <td>mouldivore</td>
    </tr>
    <tr>
      <td>pagelis</td>
      <td>pagelivore</td>
    </tr>
    <tr>
      <td>roadria</td>
      <td>roadrivore</td>
    </tr>
    <tr>
      <td>raileus</td>
      <td>raillivore</td>
    </tr>
    <tr>
      <td>cotanis</td>
      <td>cotanivore</td>
    </tr>
    <tr>
      <td>sequena</td>
      <td>sequnivore</td>
    </tr>
    <tr>
      <td>waretus</td>
      <td>warehivore</td>
    </tr>
    <tr>
      <td>stockii</td>
      <td>stockivore</td>
    </tr>
  </tbody>
</table>

<table>
  <thead>
    <tr>
      <th>Prefix</th>
      <th>Use Case</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Cognate</td>
      <td>Used when a function firstly accepts an operation, which will later be instantiated with the result of the main algorithm performed by the function.
      This prefix is not used when the function's name strongly suggests the operation's existence, such as <code>Agent</code>, <code>BindFront</code>, <code>BindBack</code>, and <code>Bind</code>.</td>
    </tr>
    <tr>
      <td>Kindred</td>
      <td>Used when a function lastly accepts operations or predicates that participate in the algorithm performed by the function</td>
    </tr>
  </tbody>
</table>
