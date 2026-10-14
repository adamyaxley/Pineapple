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

`FilePath::write` and the default `FileSystem::write` replace whole files
atomically. They write and flush a sibling temporary file before replacing the
destination. Empty buffers create or replace a file with an empty file. Failed
writes or replacements leave the previous destination intact and return a
`FileResult` error; only the temporary file created by that write is cleaned up.
Temporary files are created exclusively, so existing siblings (including those
left by an interrupted write) are skipped, not truncated or deleted.

Writes are serialized within the process. Callers must separately serialize an
entire read/modify/write transaction; atomic replacement alone does not prevent
lost updates. Platform overrides keep their storage restrictions: Android asset
writes still return `AccessDenied`, while internal writes use this implementation.

Replacement requires permission to create and rename files in the parent
directory, not just to modify the old file. It changes the file's identity;
existing permissions and other metadata are not copied, other hard links keep
the old contents, and a destination symbolic link is replaced rather than
followed. Temporary contents are flushed to disk, but the parent directory is
not explicitly synced, so this is not a guarantee against every power-loss
scenario. On Windows an open reader may prevent replacement; if bounded retries
fail, `write` returns `WriteError` and retains the previous destination.
