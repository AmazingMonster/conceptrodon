
# Introducation

## Vocabulary

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
            <td>A template is a metafunction if it is a class template or an alias template</td>
        </tr>
        <tr>
            <td>signature</td>
            <td>
                A signature is:
                <ul>
                    <li><code>typename</code> for a type;</li>
                    <li><code>auto</code> for a value;</li>
                    <li>the template-head for a template</li>
                </ul>
        </tr>
        <tr>
            <td>conformed</td>
            <td>
                A metafunction is conformed if one of the following is true
                <ul>
                    <li>
                        It is a class template whose parameter list only consists of type template parameters(<code>typename</code>);
                    </li>
                    <li>
                        It is a class template whose parameter list only consists of non-type template parameters(<code>auto</code>);
                    </li>
                    <li>
                        It is a class template whose parameter list only consists of conformed metafunctions
                    </li>
                </ul>
            </td>
        </tr>
        <tr>
            <td>function</td>
            <td>conformed metafunction</td>
        </tr>
        <tr>
            <td>category</td>
            <td>
                Let M be the set of all functions, define &sim; as follows: &forall; (x, y) &isin; M, x &sim; y &iff; x and y have the same signature. Then a category is an equivalence class in M under &sim;
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
            <td>holder</td>
            <td>function that transports arguments via its parameter list</td>
        </tr>
        <tr>
            <td>packed holder</td>
            <td>instantiation of a holder</td>
        </tr>
        <tr>
            <td>operation</td>
            <td>An operation is a function or an instantiation of a function. The word is used when the focus is on the function's functionality.</td>
        </tr>
        <tr>
            <td>list</td>
            <td>A list is an arrangement of tokens where tokens can be enumerated</td>
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
            <td>
                parameter(s) for a Flow
            </td>
        </tr>
        <tr>
            <td>stockroom(s)</td>
            <td>
                parameter(s) for a Sail
            </td>
        </tr>
        <tr>
            <td>container(s)</td>
            <td>
                parameter(s) for a Road or a warehouse
            </td>
        </tr>
        <tr>
            <td>sequence(s)</td>
            <td>
                parameter(s) for a Rail or a stockroom
            </td>
        </tr>
        <tr>
            <td>element(s)</td>
            <td>
                parameter(s) for a Mold or a container
            </td>
        </tr>
        <tr>
            <td>variable(s)</td>
            <td>
                parameter(s) for a Page or a sequence
            </td>
        </tr>
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
            <td>
                instantiation of a warehouse
            </td>
        </tr>
        <tr>
            <td>packed stockroom</td>
            <td>
                instantiation of a stockroom
            </td>
        </tr>
        <tr>
            <td>packed container</td>
            <td>
                instantiation of a container
            </td>
        </tr>
        <tr>
            <td>packed sequence</td>
            <td>
                instantiation of a sequence
            </td>
        </tr>
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
            <td>
                A funtion that feeds on types
            </td>
        </tr>
        <tr>
            <td>varybivore</td>
            <td>
                A funtion that feeds on variables
            </td>
        </tr>
        <tr>
            <td>mouldivore</td>
            <td>
                A funtion that feeds on Molds
            </td>
        </tr>
        <tr>
            <td>pagelivore</td>
            <td>
                A funtion that feeds on Pages
            </td>
        </tr>
        <tr>
            <td>roadrivore</td>
            <td>
                A funtion that feeds on Roads
            </td>
        </tr>
        <tr>
            <td>raillivore</td>
            <td>
                A funtion that feeds on Rails
            </td>
        </tr>
        <tr>
            <td>cotanivore</td>
            <td>
                A funtion that feeds on packed containers
            </td>
        </tr>
        <tr>
            <td>sequnivore</td>
            <td>
                A funtion that feeds on packed sequence
            </td>
        </tr>
        <tr>
            <td>warehivore</td>
            <td>
                A funtion that feeds on packed warehouses
            </td>
        </tr>
        <tr>
            <td>stockivore</td>
            <td>
                A funtion that feeds on packed stockrooms
            </td>
        </tr>
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
            <td>
                typelivore
            </td>
        </tr>
        <tr>
            <td>varbola</td>
            <td>
                varybivore
            </td>
        </tr>
        <tr>
            <td>moldiae</td>
            <td>
                mouldivore
            </td>
        </tr>
        <tr>
            <td>pagelis</td>
            <td>
                pagelivore
            </td>
        </tr>
        <tr>
            <td>roadria</td>
            <td>
                roadrivore
            </td>
        </tr>
        <tr>
            <td>raileus</td>
            <td>
                raillivore
            </td>
        </tr>
        <tr>
            <td>cotanis</td>
            <td>
                cotanivore
            </td>
        </tr>
        <tr>
            <td>sequena</td>
            <td>
                sequnivore
            </td>
        </tr>
        <tr>
            <td>waretus</td>
            <td>
                warehivore
            </td>
        </tr>
        <tr>
            <td>stockii</td>
            <td>
                stockivore
            </td>
        </tr>
</table>

