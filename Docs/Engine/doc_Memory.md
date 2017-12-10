# Header file `Memory.h`<a id="Memory.h"></a>

<pre><code class="language-cpp">namespace <a href='doc_Rect.md#Rect.h'>pa</a>
{
    namespace <a href='doc_Memory.md#Memory.h'>Memory</a>
    {
        void* <a href='doc_Memory.md#Memory.h'>allocate</a>(unsigned long size);
        
        void <a href='doc_Memory.md#Memory.h'>deallocate</a>(void*);
        
        void* <a href='doc_Memory.md#Memory.h'>reallocate</a>(void*, unsigned long size);
    }
}</code></pre>

-----
