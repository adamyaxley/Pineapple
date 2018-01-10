# Header file `World.h`<a id="World.h"></a>

<pre><code class="language-cpp">namespace <a href='doc_Rect.md#Rect.h'>pa</a>
{
    class <a href='doc_World.md#pa::World'>World</a>;
}</code></pre>

## Class `pa::World`<a id="pa::World"></a>

<pre><code class="language-cpp">class World
{
public:
    using <a href='doc_World.md#pa::World'>Callback</a> = <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::function%3cvoid(World&,constInput&input)%3e'>std::function&lt;void(World&amp;, const Input&amp;input)&gt;</a>;
    
    using <a href='doc_World.md#pa::World'>CallbackContainer</a> = <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::list%3cCallback%3e'>std::list&lt;Callback&gt;</a>;
    
    using <a href='doc_World.md#pa::World'>CallbackIterator</a> = CallbackContainer::const_iterator;
    
    <a href='doc_World.md#pa::World::World()'>World</a>();
    
    <a href='doc_World.md#pa::World::World(std::shared_ptr-Platform-)'>World</a>(<a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cPlatform%3e'>std::shared_ptr&lt;Platform&gt;</a> platform);
    
    <a href='doc_World.md#pa::World::World(constpa::World&)'>World</a>(const <a href='doc_World.md#pa::World'>World</a>&amp; copy) = delete;
    
    <a href='doc_World.md#pa::World::World(pa::World&&)'>World</a>(<a href='doc_World.md#pa::World'>World</a>&amp;&amp; move) = default;
    
    <a href='doc_World.md#pa::World'>World</a>&amp; <a href='doc_World.md#pa::World::operator=(constpa::World&)'>operator=</a>(const <a href='doc_World.md#pa::World'>World</a>&amp; copy) = delete;
    
    <a href='doc_World.md#pa::World'>World</a>&amp; <a href='doc_World.md#pa::World::operator=(pa::World&&)'>operator=</a>(<a href='doc_World.md#pa::World'>World</a>&amp;&amp; move) = default;
    
    <a href='doc_World.md#pa::World::~World()'>~World</a>();
    
    <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cPlatform%3e'>std::shared_ptr&lt;Platform&gt;</a> <a href='doc_World.md#pa::World::getPlatform()'>getPlatform</a>();
    
    bool <a href='doc_World.md#pa::World::step(Time,constpa::Input&)'>step</a>(<a href='doc_Time.md#Time.h'>Time</a> deltaTime, const <a href='doc_Input.md#Input.h'>Input</a>&amp; input = Input());
    
    void <a href='doc_World.md#pa::World::end()'>end</a>();
    
    template &lt;typename T, typename ... Args&gt;
    void <a href='doc_World.md#pa::World::resetNextStep(Args&&...)'>resetNextStep</a>(Args&amp;&amp;... args);
    
    template &lt;typename T, typename ... Args&gt;
    <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cT%3e'>std::shared_ptr&lt;T&gt;</a> <a href='doc_World.md#pa::World::create(Args&&...)'>create</a>(Args&amp;&amp;... args);
    
    template &lt;typename T&gt;
    const <a href='doc_ObjectInfo.md#ObjectInfo.h'>pa::ObjectList&lt;T&gt;</a>&amp; <a href='doc_World.md#pa::World::getList()'>getList</a>();
    
    template &lt;typename T&gt;
    const <a href='doc_ObjectInfo.md#ObjectInfo.h'>pa::ObjectList&lt;T&gt;</a>&amp; <a href='doc_World.md#pa::World::getChildList()'>getChildList</a>();
    
    template &lt;typename T&gt;
    void <a href='doc_World.md#pa::World::setPriority(int)'>setPriority</a>(int priority);
    
    template &lt;typename T&gt;
    int <a href='doc_World.md#pa::World::getPriority()'>getPriority</a>();
    
    <a href='doc_Time.md#Time.h'>Time</a> <a href='doc_World.md#pa::World::getTime()const'>getTime</a>() const;
    
    int <a href='doc_World.md#pa::World::getTicks()const'>getTicks</a>() const;
    
    template &lt;typename T&gt;
    <a href='doc_World.md#pa::World'>World::CallbackIterator</a> <a href='doc_World.md#pa::World::registerPreStepInstancesCallback(T&&)'>registerPreStepInstancesCallback</a>(T&amp;&amp; callback);
    
    void <a href='doc_World.md#pa::World::unregisterPreStepInstancesCallback(World::CallbackIterator)'>unregisterPreStepInstancesCallback</a>(<a href='doc_World.md#pa::World'>World::CallbackIterator</a> iterator);
    
    template &lt;typename T&gt;
    <a href='doc_World.md#pa::World'>World::CallbackIterator</a> <a href='doc_World.md#pa::World::registerPostStepInstancesCallback(T&&)'>registerPostStepInstancesCallback</a>(T&amp;&amp; callback);
    
    void <a href='doc_World.md#pa::World::unregisterPostStepInstancesCallback(World::CallbackIterator)'>unregisterPostStepInstancesCallback</a>(<a href='doc_World.md#pa::World'>World::CallbackIterator</a> iterator);
};</code></pre>

A World manages the lifetime and interaction of all objects that have been created inside it.

### Default constructor `pa::World::World`<a id="pa::World::World()"></a>

<pre><code class="language-cpp">World();</code></pre>

Basic constructor to create a fresh new World.

### Constructor `pa::World::World`<a id="pa::World::World(std::shared_ptr-Platform-)"></a>

<pre><code class="language-cpp">World(<a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cPlatform%3e'>std::shared_ptr&lt;Platform&gt;</a> platform);</code></pre>

Creates a World

**Parameters:**

  - <a id="pa::World::World(std::shared_ptr-Platform-).platform"></a>`platform` - The Platform to store inside the world The World doesn't actually use the Platform in any way, it is only provided so that it can be accessed conveniently by calling getPlatform()

### Copy constructor `pa::World::World`<a id="pa::World::World(constpa::World&)"></a>

<pre><code class="language-cpp">World(const <a href='doc_World.md#pa::World'>World</a>&amp; copy) = delete;</code></pre>

Do not allow copy construction

### Move constructor `pa::World::World`<a id="pa::World::World(pa::World&&)"></a>

<pre><code class="language-cpp">World(<a href='doc_World.md#pa::World'>World</a>&amp;&amp; move) = default;</code></pre>

Allow move construction

### Copy assignment operator `pa::World::operator=`<a id="pa::World::operator=(constpa::World&)"></a>

<pre><code class="language-cpp"><a href='doc_World.md#pa::World'>World</a>&amp; operator=(const <a href='doc_World.md#pa::World'>World</a>&amp; copy) = delete;</code></pre>

Do not allow copy assignment

### Move assignment operator `pa::World::operator=`<a id="pa::World::operator=(pa::World&&)"></a>

<pre><code class="language-cpp"><a href='doc_World.md#pa::World'>World</a>&amp; operator=(<a href='doc_World.md#pa::World'>World</a>&amp;&amp; move) = default;</code></pre>

Allow move assignment

### Destructor `pa::World::~World`<a id="pa::World::~World()"></a>

<pre><code class="language-cpp">~World();</code></pre>

When the world is deconstructed all objects contained within it will also be deconstructed.

### Function `pa::World::getPlatform`<a id="pa::World::getPlatform()"></a>

<pre><code class="language-cpp"><a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cPlatform%3e'>std::shared_ptr&lt;Platform&gt;</a> getPlatform();</code></pre>

*Returns*: A std::shared\_ptr to the Platform that is registered to this world.

*Notes*: The world doesn't actually use the Platform object in any way, it is only provided as a convenience function so that objects created in the world can access the current Platform.

### Function `pa::World::step`<a id="pa::World::step(Time,constpa::Input&)"></a>

<pre><code class="language-cpp">bool step(<a href='doc_Time.md#Time.h'>Time</a> deltaTime, const <a href='doc_Input.md#Input.h'>Input</a>&amp; input = Input());</code></pre>

Steps the world one step into the future, stepping all objects.

*Returns*: true if the world hasn't ended this step

*Notes*: Different types of objects will be processed according to their priority, and objects of the same type will be processed in an unspecified order, which may change between between calls to step()

**Parameters:**

  - <a id="pa::World::step(Time,constpa::Input&)"></a>`deltaTime` - How much to increment the World's time by.

  - <a id="pa::World::step(Time,constpa::Input&).input"></a>`input` - The input to the World this step, this is normally provided by pa::Platform::getInput() but could also be generated via other methods.

### Function `pa::World::end`<a id="pa::World::end()"></a>

<pre><code class="language-cpp">void end();</code></pre>

End the world, destroying all objects.

*Notes*: This is usually called when the simulation has finished and the application is closing.

### Function template `pa::World::resetNextStep`<a id="pa::World::resetNextStep(Args&&...)"></a>

<pre><code class="language-cpp">template &lt;typename T, typename ... Args&gt;
void resetNextStep(Args&amp;&amp;... args);</code></pre>

Resets the World by destroying all existing objects and then creating a single instance of `T`.

**Parameters:**

  - <a id="pa::World::resetNextStep(Args&&...).args"></a>`args` - Additional arguments to forward to the constructor of  `T` (a reference to the World is already passed as a first argument to `T`)

### Function template `pa::World::create`<a id="pa::World::create(Args&&...)"></a>

<pre><code class="language-cpp">template &lt;typename T, typename ... Args&gt;
<a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::shared_ptr%3cT%3e'>std::shared_ptr&lt;T&gt;</a> create(Args&amp;&amp;... args);</code></pre>

Creates a new instance of `T` and adds it to the world

*Returns*: A std::shared\_ptr to `T`

**Parameters:**

  - <a id="pa::World::create(Args&&...).args"></a>`args` - Additional arguments to forward to the constructor of  `T` (a reference to the World is already passed as a first argument to `T`)

### Function template `pa::World::getList`<a id="pa::World::getList()"></a>

<pre><code class="language-cpp">template &lt;typename T&gt;
const <a href='doc_ObjectInfo.md#ObjectInfo.h'>pa::ObjectList&lt;T&gt;</a>&amp; getList();</code></pre>

*Returns*: A constant reference to a list of `T`.

### Function template `pa::World::getChildList`<a id="pa::World::getChildList()"></a>

<pre><code class="language-cpp">template &lt;typename T&gt;
const <a href='doc_ObjectInfo.md#ObjectInfo.h'>pa::ObjectList&lt;T&gt;</a>&amp; getChildList();</code></pre>

*Returns*: A constant reference to the list of all children of `T`. Children are defined as instances of `T` or instances of objects that derive from	`T`. To track children of `T`, `T` must inherit from EnableChildList\<T\>.

### Function template `pa::World::setPriority`<a id="pa::World::setPriority(int)"></a>

<pre><code class="language-cpp">template &lt;typename T&gt;
void setPriority(int priority);</code></pre>

Set the priority of `T`.

*Notes*: Objects with lower priority will have their instances stepped first.

### Function template `pa::World::getPriority`<a id="pa::World::getPriority()"></a>

<pre><code class="language-cpp">template &lt;typename T&gt;
int getPriority();</code></pre>

*Returns*: The priority of `T`

*Notes*: Objects with lower priority will have their instances stepped first.

### Function `pa::World::getTime`<a id="pa::World::getTime()const"></a>

<pre><code class="language-cpp"><a href='doc_Time.md#Time.h'>Time</a> getTime() const;</code></pre>

*Returns*: The cumulative time that the has passed since the World was created

### Function `pa::World::getTicks`<a id="pa::World::getTicks()const"></a>

<pre><code class="language-cpp">int getTicks() const;</code></pre>

*Returns*: The number of ticks (number of times step() has been completely processed) since the World was created.

### Function template `pa::World::registerPreStepInstancesCallback`<a id="pa::World::registerPreStepInstancesCallback(T&&)"></a>

<pre><code class="language-cpp">template &lt;typename T&gt;
<a href='doc_World.md#pa::World'>World::CallbackIterator</a> registerPreStepInstancesCallback(T&amp;&amp; callback);</code></pre>

Registers a callback that will be fired before the instances are stepped.

*Returns*: A CallbackIterator that must be passed into unregisterPreStepInstancesCallback when un-registering the callback.

### Function `pa::World::unregisterPreStepInstancesCallback`<a id="pa::World::unregisterPreStepInstancesCallback(World::CallbackIterator)"></a>

<pre><code class="language-cpp">void unregisterPreStepInstancesCallback(<a href='doc_World.md#pa::World'>World::CallbackIterator</a> iterator);</code></pre>

Un-registers an existing callback that was registered by registerPreStepInstancesCallback.

*Remarks*: after calling this function `iterator` will be invalidated.

### Function template `pa::World::registerPostStepInstancesCallback`<a id="pa::World::registerPostStepInstancesCallback(T&&)"></a>

<pre><code class="language-cpp">template &lt;typename T&gt;
<a href='doc_World.md#pa::World'>World::CallbackIterator</a> registerPostStepInstancesCallback(T&amp;&amp; callback);</code></pre>

Registers a callback that will be fired after the instances are stepped.

*Returns*: A CallbackIterator that must be passed into unregisterPostStepInstancesCallback when un-registering the callback.

### Function `pa::World::unregisterPostStepInstancesCallback`<a id="pa::World::unregisterPostStepInstancesCallback(World::CallbackIterator)"></a>

<pre><code class="language-cpp">void unregisterPostStepInstancesCallback(<a href='doc_World.md#pa::World'>World::CallbackIterator</a> iterator);</code></pre>

Un-registers an existing callback that was registered by registerPostStepInstancesCallback.

*Remarks*: after calling this function `iterator` will be invalidated.

-----

-----
