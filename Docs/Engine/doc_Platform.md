# Header file `Platform.h`<a id="Platform.h"></a>

<pre><code class="language-cpp">namespace <a href='doc_Rect.md#Rect.h'>pa</a>
{
    struct <a href='doc_Platform.md#Platform.h'>Arguments</a>;
    
    int <a href='doc_Platform.md#Platform.h'>Main</a>(<a href='doc_Platform.md#Platform.h'>Arguments</a>*);
    
    namespace <a href='doc_Platform.md#Platform.h'>Make</a>
    {
        <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cPlatform%3e'>std::shared_ptr&lt;Platform&gt;</a> <a href='doc_Platform.md#Platform.h'>platform</a>(<a href='doc_Platform.md#Platform.h'>Arguments</a>* arguments, const <a href='doc_PlatformSettings.md#PlatformSettings.h'>PlatformSettings</a>&amp; settings);
    }
    
    class <a href='doc_Platform.md#Platform.h'>Platform</a>;
}</code></pre>

-----

Applications control the frame loop using `Platform::pollEvents`, their game
update, and `Platform::idle`. Skip `idle` when the update ends the loop so the
worker does not enter another render barrier.

On iOS, the worker entry point covers startup and shutdown with an autorelease
pool. Applications should compile their loop as Objective-C++ on iOS and wrap
each iteration in a nested `@autoreleasepool`, including `pollEvents`, the game
update, and `idle`. This drains temporary ownership after rendering finishes
and on the final iteration's `break`. Objects retained for later callbacks
remain alive.
