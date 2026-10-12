# Header file `FileSystem.h`<a id="FileSystem.h"></a>

<pre><code class="language-cpp">namespace <a href='doc_Rect.md#Rect.h'>pa</a>
{
    namespace <a href='doc_Graphics.md#Graphics.h'>MakeInternal</a>
    {
        <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::unique_ptr%3cFileSystem%3e'>std::unique_ptr&lt;FileSystem&gt;</a> <a href='doc_FileSystem.md#FileSystem.h'>fileSystem</a>(PlatformSettings::FileSystem settings);
    }
    
    enum class <a href='doc_FileSystem.md#FileSystem.h'>FileStorage</a>;
    
    enum class <a href='doc_FileSystem.md#FileSystem.h'>FileResult</a>;
    
    class <a href='doc_FileSystem.md#FileSystem.h'>FileBuffer</a>;
    
    class <a href='doc_FileSystem.md#FileSystem.h'>FilePath</a>;
    
    class <a href='doc_FileSystem.md#FileSystem.h'>FileSystem</a>;
}</code></pre>

-----

`FilePath::writeAtomically` writes and flushes a sibling temporary file before
replacing the destination. Failed writes or replacements leave the previous
destination intact and return a `FileResult` error. Atomic writes are serialized
within the process. Callers must separately serialize an entire read/modify/write
transaction; atomic replacement alone does not prevent lost updates.
