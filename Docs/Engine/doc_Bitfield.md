# Header file `Bitfield.h`<a id="Bitfield.h"></a>

<pre><code class="language-cpp">namespace 
{
    template &lt;int N&gt;
    struct <a href='doc_Bitfield.md#Bitfield.h'>BitfieldType</a>;
    
    template &lt;&gt;
    struct <a href='doc_Bitfield.md#Bitfield.h'>BitfieldType&lt;8&gt;</a>;
    
    template &lt;&gt;
    struct <a href='doc_Bitfield.md#Bitfield.h'>BitfieldType&lt;16&gt;</a>;
    
    template &lt;&gt;
    struct <a href='doc_Bitfield.md#Bitfield.h'>BitfieldType&lt;32&gt;</a>;
    
    template &lt;&gt;
    struct <a href='doc_Bitfield.md#Bitfield.h'>BitfieldType&lt;64&gt;</a>;
    
    template &lt;typename T, typename = typename std::enable_if&lt;std::is_integral&lt;T&gt;::value&gt;::type, typename = typename std::enable_if&lt;std::is_unsigned&lt;T&gt;::value&gt;::type&gt;
    constexpr T <a href='doc_Bitfield.md#Bitfield.h'>roundUpToNextPowerOf2</a>(T value, unsigned maxb = sizeof(T)*8, unsigned curb = 1);
    
    template &lt;typename T&gt;
    constexpr T <a href='doc_Bitfield.md#Bitfield.h'>atLeast8</a>(T a);
}

namespace <a href='doc_Rect.md#Rect.h'>pa</a>
{
    template &lt;typename T&gt;
    class <a href='doc_Bitfield.md#Bitfield.h'>Bitfield</a>;
}</code></pre>
