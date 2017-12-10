# Header file `Asset.h`<a id="Asset.h"></a>

<pre><code class="language-cpp">namespace <a href='doc_Rect.md#Rect.h'>pa</a>
{
    namespace <a href='doc_Asset.md#Asset.h'>Asset</a>
    {
        void <a href='doc_Asset.md#Asset.h'>load</a>(<a href='doc_Graphics.md#Graphics.h'>Graphics</a>&amp; graphics);
        
        namespace <a href='doc_Asset.md#Asset.h'>Texture</a>
        {
            <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cpa::Texture%3e'>std::shared_ptr&lt;pa::Texture&gt;</a> <a href='doc_Asset.md#Asset.h'>getPixelTexture</a>();
        }
        
        namespace <a href='doc_Asset.md#Asset.h'>Font</a>
        {
        }
        
        namespace <a href='doc_Asset.md#Asset.h'>Shader</a>
        {
            <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cpa::Shader%3e'>std::shared_ptr&lt;pa::Shader&gt;</a> <a href='doc_Asset.md#Asset.h'>getQuadFragShader</a>();
            
            <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cpa::Shader%3e'>std::shared_ptr&lt;pa::Shader&gt;</a> <a href='doc_Asset.md#Asset.h'>getQuadVertShader</a>();
            
            <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cpa::Shader%3e'>std::shared_ptr&lt;pa::Shader&gt;</a> <a href='doc_Asset.md#Asset.h'>getPassVertShader</a>();
        }
    }
}</code></pre>

-----

-----
